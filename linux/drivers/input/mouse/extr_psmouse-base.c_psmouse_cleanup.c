#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
struct serio {struct serio* parent; TYPE_1__ id; } ;
struct TYPE_6__ {TYPE_2__* serio; } ;
struct psmouse {int /*<<< orphan*/  (* pt_deactivate ) (struct psmouse*) ;TYPE_3__ ps2dev; int /*<<< orphan*/  (* cleanup ) (struct psmouse*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_ENABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_DIS ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 scalar_t__ SERIO_PS_PSTHRU ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ps2_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_mutex ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,int /*<<< orphan*/ ) ; 
 struct psmouse* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 
 int /*<<< orphan*/  stub2 (struct psmouse*) ; 

__attribute__((used)) static void psmouse_cleanup(struct serio *serio)
{
	struct psmouse *psmouse = serio_get_drvdata(serio);
	struct psmouse *parent = NULL;

	mutex_lock(&psmouse_mutex);

	if (serio->parent && serio->id.type == SERIO_PS_PSTHRU) {
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	}

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	/*
	 * Disable stream mode so cleanup routine can proceed undisturbed.
	 */
	if (ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_DISABLE))
		psmouse_warn(psmouse, "Failed to disable mouse on %s\n",
			     psmouse->ps2dev.serio->phys);

	if (psmouse->cleanup)
		psmouse->cleanup(psmouse);

	/*
	 * Reset the mouse to defaults (bare PS/2 protocol).
	 */
	ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);

	/*
	 * Some boxes, such as HP nx7400, get terribly confused if mouse
	 * is not fully enabled before suspending/shutting down.
	 */
	ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_ENABLE);

	if (parent) {
		if (parent->pt_deactivate)
			parent->pt_deactivate(parent);

		psmouse_activate(parent);
	}

	mutex_unlock(&psmouse_mutex);
}