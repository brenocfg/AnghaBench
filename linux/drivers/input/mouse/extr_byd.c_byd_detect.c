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
typedef  int u8 ;
struct ps2dev {int dummy; } ;
struct psmouse {char* vendor; char* name; struct ps2dev ps2dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 scalar_t__ ps2_command (struct ps2dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*) ; 

int byd_detect(struct psmouse *psmouse, bool set_properties)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	u8 param[4] = {0x03, 0x00, 0x00, 0x00};

	if (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		return -1;
	if (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		return -1;
	if (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		return -1;
	if (ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES))
		return -1;
	if (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		return -1;

	if (param[1] != 0x03 || param[2] != 0x64)
		return -ENODEV;

	psmouse_dbg(psmouse, "BYD touchpad detected\n");

	if (set_properties) {
		psmouse->vendor = "BYD";
		psmouse->name = "TouchPad";
	}

	return 0;
}