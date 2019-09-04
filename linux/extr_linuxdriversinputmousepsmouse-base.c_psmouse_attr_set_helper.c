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
struct psmouse_attribute {int (* set ) (struct psmouse*,int /*<<< orphan*/ ,char const*,size_t) ;scalar_t__ protect; int /*<<< orphan*/  data; } ;
struct psmouse {scalar_t__ state; TYPE_2__* protocol; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {struct device_attribute dattr; } ;
struct TYPE_5__ {scalar_t__ smbus_companion; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ PSMOUSE_IGNORE ; 
 scalar_t__ SERIO_PS_PSTHRU ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 TYPE_3__ psmouse_attr_protocol ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_mutex ; 
 struct psmouse* serio_get_drvdata (struct serio*) ; 
 int stub1 (struct psmouse*,int /*<<< orphan*/ ,char const*,size_t) ; 
 struct psmouse_attribute* to_psmouse_attr (struct device_attribute*) ; 
 struct serio* to_serio_port (struct device*) ; 

ssize_t psmouse_attr_set_helper(struct device *dev, struct device_attribute *devattr,
				const char *buf, size_t count)
{
	struct serio *serio = to_serio_port(dev);
	struct psmouse_attribute *attr = to_psmouse_attr(devattr);
	struct psmouse *psmouse, *parent = NULL;
	int retval;

	retval = mutex_lock_interruptible(&psmouse_mutex);
	if (retval)
		goto out;

	psmouse = serio_get_drvdata(serio);

	if (psmouse->protocol->smbus_companion &&
			devattr != &psmouse_attr_protocol.dattr) {
		retval = -ENOENT;
		goto out_unlock;
	}

	if (attr->protect) {
		if (psmouse->state == PSMOUSE_IGNORE) {
			retval = -ENODEV;
			goto out_unlock;
		}

		if (serio->parent && serio->id.type == SERIO_PS_PSTHRU) {
			parent = serio_get_drvdata(serio->parent);
			psmouse_deactivate(parent);
		}

		if (!psmouse->protocol->smbus_companion)
			psmouse_deactivate(psmouse);
	}

	retval = attr->set(psmouse, attr->data, buf, count);

	if (attr->protect) {
		if (retval != -ENODEV && !psmouse->protocol->smbus_companion)
			psmouse_activate(psmouse);

		if (parent)
			psmouse_activate(parent);
	}

 out_unlock:
	mutex_unlock(&psmouse_mutex);
 out:
	return retval;
}