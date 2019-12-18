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
struct psmouse {char* vendor; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYTP_CMD_READ_CYPRESS_ID ; 
 int ENODEV ; 
 scalar_t__ cypress_send_ext_cmd (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 

int cypress_detect(struct psmouse *psmouse, bool set_properties)
{
	unsigned char param[3];

	if (cypress_send_ext_cmd(psmouse, CYTP_CMD_READ_CYPRESS_ID, param))
		return -ENODEV;

	/* Check for Cypress Trackpad signature bytes: 0x33 0xCC */
	if (param[0] != 0x33 || param[1] != 0xCC)
		return -ENODEV;

	if (set_properties) {
		psmouse->vendor = "Cypress";
		psmouse->name = "Trackpad";
	}

	return 0;
}