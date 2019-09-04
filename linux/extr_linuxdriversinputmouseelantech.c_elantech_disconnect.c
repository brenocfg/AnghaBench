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
struct TYPE_6__ {TYPE_2__* serio; } ;
struct psmouse {struct elantech_data* private; TYPE_3__ ps2dev; } ;
struct elantech_data {scalar_t__ tp_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  elantech_attr_group ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct elantech_data*) ; 
 int /*<<< orphan*/  psmouse_smbus_cleanup (struct psmouse*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void elantech_disconnect(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;

	/*
	 * We might have left a breadcrumb when trying to
	 * set up SMbus companion.
	 */
	psmouse_smbus_cleanup(psmouse);

	if (etd->tp_dev)
		input_unregister_device(etd->tp_dev);
	sysfs_remove_group(&psmouse->ps2dev.serio->dev.kobj,
			   &elantech_attr_group);
	kfree(psmouse->private);
	psmouse->private = NULL;
}