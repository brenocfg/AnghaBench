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
typedef  int u8 ;
struct ps2dev {TYPE_1__* serio; } ;
struct psmouse {struct ps2dev ps2dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETID ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_DIS ; 
 int ps2_command (struct ps2dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int psmouse_probe(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[2];
	int error;

	/*
	 * First, we check if it's a mouse. It should send 0x00 or 0x03 in
	 * case of an IntelliMouse in 4-byte mode or 0x04 for IM Explorer.
	 * Sunrex K8561 IR Keyboard/Mouse reports 0xff on second and
	 * subsequent ID queries, probably due to a firmware bug.
	 */
	param[0] = 0xa5;
	error = ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);
	if (error)
		return error;

	if (param[0] != 0x00 && param[0] != 0x03 &&
	    param[0] != 0x04 && param[0] != 0xff)
		return -ENODEV;

	/*
	 * Then we reset and disable the mouse so that it doesn't generate
	 * events.
	 */
	error = ps2_command(ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);
	if (error)
		psmouse_warn(psmouse, "Failed to reset mouse on %s: %d\n",
			     ps2dev->serio->phys, error);

	return 0;
}