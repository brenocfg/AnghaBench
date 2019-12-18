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
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_WRAP ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE21 ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alps_monitor_mode(struct psmouse *psmouse, bool enable)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;

	if (enable) {
		/* EC E9 F5 F5 E7 E6 E7 E9 to enter monitor mode */
		if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_RESET_WRAP) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_GETINFO) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSCALE21) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSCALE11) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSCALE21) ||
		    ps2_command(ps2dev, NULL, PSMOUSE_CMD_GETINFO))
			return -1;
	} else {
		/* EC to exit monitor mode */
		if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_RESET_WRAP))
			return -1;
	}

	return 0;
}