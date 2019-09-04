#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mouse_kind; int /*<<< orphan*/  input; } ;

/* Variables and functions */
#define  ADBMOUSE_MACALLY2 132 
#define  ADBMOUSE_MICROSPEED 131 
#define  ADBMOUSE_MS_A3 130 
#define  ADBMOUSE_TRACKBALLPRO 129 
#define  ADBMOUSE_TRACKPAD 128 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 TYPE_1__** adbhid ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void
adbhid_mouse_input(unsigned char *data, int nb, int autopoll)
{
	int id = (data[0] >> 4) & 0x0f;

	if (!adbhid[id]) {
		pr_err("ADB HID on ID %d not yet registered\n", id);
		return;
	}

  /*
    Handler 1 -- 100cpi original Apple mouse protocol.
    Handler 2 -- 200cpi original Apple mouse protocol.

    For Apple's standard one-button mouse protocol the data array will
    contain the following values:

                BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Talk, register 0, for device dddd.
    data[1] = bxxx xxxx First button and x-axis motion.
    data[2] = byyy yyyy Second button and y-axis motion.

    Handler 4 -- Apple Extended mouse protocol.

    For Apple's 3-button mouse protocol the data array will contain the
    following values:

		BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Talk, register 0, for device dddd.
    data[1] = bxxx xxxx Left button and x-axis motion.
    data[2] = byyy yyyy Second button and y-axis motion.
    data[3] = byyy bxxx Third button and fourth button.  Y is additional
	      high bits of y-axis motion.  XY is additional
	      high bits of x-axis motion.

    MacAlly 2-button mouse protocol.

    For MacAlly 2-button mouse protocol the data array will contain the
    following values:

		BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Talk, register 0, for device dddd.
    data[1] = bxxx xxxx Left button and x-axis motion.
    data[2] = byyy yyyy Right button and y-axis motion.
    data[3] = ???? ???? unknown
    data[4] = ???? ???? unknown

  */

	/* If it's a trackpad, we alias the second button to the first.
	   NOTE: Apple sends an ADB flush command to the trackpad when
	         the first (the real) button is released. We could do
		 this here using async flush requests.
	*/
	switch (adbhid[id]->mouse_kind)
	{
	    case ADBMOUSE_TRACKPAD:
		data[1] = (data[1] & 0x7f) | ((data[1] & data[2]) & 0x80);
		data[2] = data[2] | 0x80;
		break;
	    case ADBMOUSE_MICROSPEED:
		data[1] = (data[1] & 0x7f) | ((data[3] & 0x01) << 7);
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x02) << 6);
		data[3] = (data[3] & 0x77) | ((data[3] & 0x04) << 5)
			| (data[3] & 0x08);
		break;
	    case ADBMOUSE_TRACKBALLPRO:
		data[1] = (data[1] & 0x7f) | (((data[3] & 0x04) << 5)
			& ((data[3] & 0x08) << 4));
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x01) << 7);
		data[3] = (data[3] & 0x77) | ((data[3] & 0x02) << 6);
		break;
	    case ADBMOUSE_MS_A3:
		data[1] = (data[1] & 0x7f) | ((data[3] & 0x01) << 7);
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x02) << 6);
		data[3] = ((data[3] & 0x04) << 5);
		break;
            case ADBMOUSE_MACALLY2:
		data[3] = (data[2] & 0x80) ? 0x80 : 0x00;
		data[2] |= 0x80;  /* Right button is mapped as button 3 */
		nb=4;
                break;
	}

	input_report_key(adbhid[id]->input, BTN_LEFT,   !((data[1] >> 7) & 1));
	input_report_key(adbhid[id]->input, BTN_MIDDLE, !((data[2] >> 7) & 1));

	if (nb >= 4 && adbhid[id]->mouse_kind != ADBMOUSE_TRACKPAD)
		input_report_key(adbhid[id]->input, BTN_RIGHT,  !((data[3] >> 7) & 1));

	input_report_rel(adbhid[id]->input, REL_X,
			 ((data[2]&0x7f) < 64 ? (data[2]&0x7f) : (data[2]&0x7f)-128 ));
	input_report_rel(adbhid[id]->input, REL_Y,
			 ((data[1]&0x7f) < 64 ? (data[1]&0x7f) : (data[1]&0x7f)-128 ));

	input_sync(adbhid[id]->input);
}