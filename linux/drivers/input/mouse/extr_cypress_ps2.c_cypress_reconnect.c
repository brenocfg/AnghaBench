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
 int CYTP_PS2_CMD_TRIES ; 
 int cypress_detect (struct psmouse*,int) ; 
 int /*<<< orphan*/  cypress_reset (struct psmouse*) ; 
 scalar_t__ cypress_set_absolute_mode (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 

__attribute__((used)) static int cypress_reconnect(struct psmouse *psmouse)
{
	int tries = CYTP_PS2_CMD_TRIES;
	int rc;

	do {
		cypress_reset(psmouse);
		rc = cypress_detect(psmouse, false);
	} while (rc && (--tries > 0));

	if (rc) {
		psmouse_err(psmouse, "Reconnect: unable to detect trackpad.\n");
		return -1;
	}

	if (cypress_set_absolute_mode(psmouse)) {
		psmouse_err(psmouse, "Reconnect: Unable to initialize Cypress absolute mode.\n");
		return -1;
	}

	return 0;
}