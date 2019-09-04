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
struct TYPE_3__ {scalar_t__ type; } ;
struct serio {struct serio* parent; TYPE_1__ id; } ;
struct psmouse {int (* fast_reconnect ) (struct psmouse*) ;int (* reconnect ) (struct psmouse*) ;TYPE_2__* protocol; int /*<<< orphan*/  (* pt_activate ) (struct psmouse*) ;} ;
typedef  enum psmouse_type { ____Placeholder_psmouse_type } psmouse_type ;
struct TYPE_4__ {int type; int /*<<< orphan*/  smbus_companion; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 scalar_t__ SERIO_PS_PSTHRU ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 
 int psmouse_extensions (struct psmouse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psmouse_initialize (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_max_proto ; 
 int /*<<< orphan*/  psmouse_mutex ; 
 scalar_t__ psmouse_probe (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 struct psmouse* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 

__attribute__((used)) static int __psmouse_reconnect(struct serio *serio, bool fast_reconnect)
{
	struct psmouse *psmouse = serio_get_drvdata(serio);
	struct psmouse *parent = NULL;
	int (*reconnect_handler)(struct psmouse *);
	enum psmouse_type type;
	int rc = -1;

	mutex_lock(&psmouse_mutex);

	if (fast_reconnect) {
		reconnect_handler = psmouse->fast_reconnect;
		if (!reconnect_handler) {
			rc = -ENOENT;
			goto out_unlock;
		}
	} else {
		reconnect_handler = psmouse->reconnect;
	}

	if (serio->parent && serio->id.type == SERIO_PS_PSTHRU) {
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	}

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	if (reconnect_handler) {
		if (reconnect_handler(psmouse))
			goto out;
	} else {
		psmouse_reset(psmouse);

		if (psmouse_probe(psmouse) < 0)
			goto out;

		type = psmouse_extensions(psmouse, psmouse_max_proto, false);
		if (psmouse->protocol->type != type)
			goto out;
	}

	/*
	 * OK, the device type (and capabilities) match the old one,
	 * we can continue using it, complete initialization
	 */
	if (!psmouse->protocol->smbus_companion) {
		psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
		psmouse_initialize(psmouse);
	}

	if (parent && parent->pt_activate)
		parent->pt_activate(parent);

	/*
	 * PS/2 devices having SMBus companions should stay disabled
	 * on PS/2 side, in order to have SMBus part operable.
	 */
	if (!psmouse->protocol->smbus_companion)
		psmouse_activate(psmouse);

	rc = 0;

out:
	/* If this is a pass-through port the parent waits to be activated */
	if (parent)
		psmouse_activate(parent);

out_unlock:
	mutex_unlock(&psmouse_mutex);
	return rc;
}