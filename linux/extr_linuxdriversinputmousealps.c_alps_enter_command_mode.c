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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_WRAP ; 
 int /*<<< orphan*/  alps_check_valid_firmware_id (unsigned char*) ; 
 scalar_t__ alps_rpt_cmd (struct psmouse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 

__attribute__((used)) static int alps_enter_command_mode(struct psmouse *psmouse)
{
	unsigned char param[4];

	if (alps_rpt_cmd(psmouse, 0, PSMOUSE_CMD_RESET_WRAP, param)) {
		psmouse_err(psmouse, "failed to enter command mode\n");
		return -1;
	}

	if (!alps_check_valid_firmware_id(param)) {
		psmouse_dbg(psmouse,
			    "unknown response while entering command mode\n");
		return -1;
	}
	return 0;
}