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
typedef  unsigned int u32 ;
struct psmouse {unsigned char* packet; struct elantech_data* private; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int debug; } ;
struct elantech_data {TYPE_1__ info; struct input_dev* tp_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  elantech_packet_dump (struct psmouse*) ; 
 unsigned int get_unaligned_le32 (unsigned char*) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,unsigned char) ; 

__attribute__((used)) static void elantech_report_trackpoint(struct psmouse *psmouse,
				       int packet_type)
{
	/*
	 * byte 0:  0   0  sx  sy   0   M   R   L
	 * byte 1:~sx   0   0   0   0   0   0   0
	 * byte 2:~sy   0   0   0   0   0   0   0
	 * byte 3:  0   0 ~sy ~sx   0   1   1   0
	 * byte 4: x7  x6  x5  x4  x3  x2  x1  x0
	 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
	 *
	 * x and y are written in two's complement spread
	 * over 9 bits with sx/sy the relative top bit and
	 * x7..x0 and y7..y0 the lower bits.
	 * The sign of y is opposite to what the input driver
	 * expects for a relative movement
	 */

	struct elantech_data *etd = psmouse->private;
	struct input_dev *tp_dev = etd->tp_dev;
	unsigned char *packet = psmouse->packet;
	int x, y;
	u32 t;

	t = get_unaligned_le32(&packet[0]);

	switch (t & ~7U) {
	case 0x06000030U:
	case 0x16008020U:
	case 0x26800010U:
	case 0x36808000U:
		x = packet[4] - (int)((packet[1]^0x80) << 1);
		y = (int)((packet[2]^0x80) << 1) - packet[5];

		psmouse_report_standard_buttons(tp_dev, packet[0]);

		input_report_rel(tp_dev, REL_X, x);
		input_report_rel(tp_dev, REL_Y, y);

		input_sync(tp_dev);

		break;

	default:
		/* Dump unexpected packet sequences if debug=1 (default) */
		if (etd->info.debug == 1)
			elantech_packet_dump(psmouse);

		break;
	}
}