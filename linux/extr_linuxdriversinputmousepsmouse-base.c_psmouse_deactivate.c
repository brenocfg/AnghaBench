#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* serio; } ;
struct psmouse {TYPE_2__ ps2dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 int ps2_command (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,int /*<<< orphan*/ ,int) ; 

int psmouse_deactivate(struct psmouse *psmouse)
{
	int error;

	error = ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_DISABLE);
	if (error) {
		psmouse_warn(psmouse, "Failed to deactivate mouse on %s: %d\n",
			     psmouse->ps2dev.serio->phys, error);
		return error;
	}

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
	return 0;
}