#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ps2dev {int dummy; } ;
struct psmouse {struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETPOLL ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSTREAM ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alps_get_otp_values_ss4_v2(struct psmouse *psmouse,
				      unsigned char index, unsigned char otp[])
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;

	switch (index) {
	case 0:
		if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSTREAM)  ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSTREAM)  ||
		    ps2_command(ps2dev, otp, PSMOUSE_CMD_GETINFO))
			return -1;

		break;

	case 1:
		if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETPOLL)  ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETPOLL)  ||
		    ps2_command(ps2dev, otp, PSMOUSE_CMD_GETINFO))
			return -1;

		break;
	}

	return 0;
}