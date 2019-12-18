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
struct psmouse {char* vendor; char* name; struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_FW_VERSION_QUERY ; 
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_DIS ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  elantech_is_signature_valid (unsigned char*) ; 
 scalar_t__ ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,...) ; 
 scalar_t__ synaptics_send_cmd (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 

int elantech_detect(struct psmouse *psmouse, bool set_properties)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[3];

	ps2_command(ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);

	if (ps2_command(ps2dev,  NULL, PSMOUSE_CMD_DISABLE) ||
	    ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE11) ||
	    ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO)) {
		psmouse_dbg(psmouse, "sending Elantech magic knock failed.\n");
		return -1;
	}

	/*
	 * Report this in case there are Elantech models that use a different
	 * set of magic numbers
	 */
	if (param[0] != 0x3c || param[1] != 0x03 ||
	    (param[2] != 0xc8 && param[2] != 0x00)) {
		psmouse_dbg(psmouse,
			    "unexpected magic knock result 0x%02x, 0x%02x, 0x%02x.\n",
			    param[0], param[1], param[2]);
		return -1;
	}

	/*
	 * Query touchpad's firmware version and see if it reports known
	 * value to avoid mis-detection. Logitech mice are known to respond
	 * to Elantech magic knock and there might be more.
	 */
	if (synaptics_send_cmd(psmouse, ETP_FW_VERSION_QUERY, param)) {
		psmouse_dbg(psmouse, "failed to query firmware version.\n");
		return -1;
	}

	psmouse_dbg(psmouse,
		    "Elantech version query result 0x%02x, 0x%02x, 0x%02x.\n",
		    param[0], param[1], param[2]);

	if (!elantech_is_signature_valid(param)) {
		psmouse_dbg(psmouse,
			    "Probably not a real Elantech touchpad. Aborting.\n");
		return -1;
	}

	if (set_properties) {
		psmouse->vendor = "Elantech";
		psmouse->name = "Touchpad";
	}

	return 0;
}