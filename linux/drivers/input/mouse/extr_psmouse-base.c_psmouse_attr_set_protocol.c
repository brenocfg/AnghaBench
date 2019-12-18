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
struct TYPE_4__ {scalar_t__ type; } ;
struct serio {scalar_t__ parent; TYPE_2__ id; int /*<<< orphan*/ * drv; int /*<<< orphan*/  children; } ;
typedef  struct psmouse_protocol {scalar_t__ smbus_companion; } const psmouse_protocol ;
struct TYPE_3__ {struct serio* serio; } ;
struct psmouse {int /*<<< orphan*/  (* pt_activate ) (struct psmouse*) ;struct input_dev* dev; int /*<<< orphan*/  (* disconnect ) (struct psmouse*) ;struct psmouse_protocol const* protocol; int /*<<< orphan*/  (* pt_deactivate ) (struct psmouse*) ;TYPE_1__ ps2dev; } ;
struct input_dev {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 size_t ENODEV ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 int /*<<< orphan*/  PSMOUSE_IGNORE ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 scalar_t__ SERIO_PS_PSTHRU ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psmouse_drv ; 
 int /*<<< orphan*/  psmouse_initialize (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_mutex ; 
 struct psmouse_protocol const* psmouse_protocol_by_name (char const*,size_t) ; 
 struct psmouse_protocol const* psmouse_protocols ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 scalar_t__ psmouse_switch_protocol (struct psmouse*,struct psmouse_protocol const*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 
 struct psmouse* serio_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  serio_unregister_child_port (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 
 int /*<<< orphan*/  stub2 (struct psmouse*) ; 
 int /*<<< orphan*/  stub3 (struct psmouse*) ; 
 int /*<<< orphan*/  stub4 (struct psmouse*) ; 

__attribute__((used)) static ssize_t psmouse_attr_set_protocol(struct psmouse *psmouse, void *data, const char *buf, size_t count)
{
	struct serio *serio = psmouse->ps2dev.serio;
	struct psmouse *parent = NULL;
	struct input_dev *old_dev, *new_dev;
	const struct psmouse_protocol *proto, *old_proto;
	int error;
	int retry = 0;

	proto = psmouse_protocol_by_name(buf, count);
	if (!proto)
		return -EINVAL;

	if (psmouse->protocol == proto)
		return count;

	new_dev = input_allocate_device();
	if (!new_dev)
		return -ENOMEM;

	while (!list_empty(&serio->children)) {
		if (++retry > 3) {
			psmouse_warn(psmouse,
				     "failed to destroy children ports, protocol change aborted.\n");
			input_free_device(new_dev);
			return -EIO;
		}

		mutex_unlock(&psmouse_mutex);
		serio_unregister_child_port(serio);
		mutex_lock(&psmouse_mutex);

		if (serio->drv != &psmouse_drv) {
			input_free_device(new_dev);
			return -ENODEV;
		}

		if (psmouse->protocol == proto) {
			input_free_device(new_dev);
			return count; /* switched by other thread */
		}
	}

	if (serio->parent && serio->id.type == SERIO_PS_PSTHRU) {
		parent = serio_get_drvdata(serio->parent);
		if (parent->pt_deactivate)
			parent->pt_deactivate(parent);
	}

	old_dev = psmouse->dev;
	old_proto = psmouse->protocol;

	if (psmouse->disconnect)
		psmouse->disconnect(psmouse);

	psmouse_set_state(psmouse, PSMOUSE_IGNORE);

	psmouse->dev = new_dev;
	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	if (psmouse_switch_protocol(psmouse, proto) < 0) {
		psmouse_reset(psmouse);
		/* default to PSMOUSE_PS2 */
		psmouse_switch_protocol(psmouse, &psmouse_protocols[0]);
	}

	psmouse_initialize(psmouse);
	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	if (psmouse->protocol->smbus_companion) {
		input_free_device(psmouse->dev);
		psmouse->dev = NULL;
	} else {
		error = input_register_device(psmouse->dev);
		if (error) {
			if (psmouse->disconnect)
				psmouse->disconnect(psmouse);

			psmouse_set_state(psmouse, PSMOUSE_IGNORE);
			input_free_device(new_dev);
			psmouse->dev = old_dev;
			psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);
			psmouse_switch_protocol(psmouse, old_proto);
			psmouse_initialize(psmouse);
			psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

			return error;
		}
	}

	if (old_dev)
		input_unregister_device(old_dev);

	if (parent && parent->pt_activate)
		parent->pt_activate(parent);

	return count;
}