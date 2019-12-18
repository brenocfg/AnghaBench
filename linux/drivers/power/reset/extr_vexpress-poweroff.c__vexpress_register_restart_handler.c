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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_active ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int register_restart_handler (int /*<<< orphan*/ *) ; 
 struct device* vexpress_restart_device ; 
 int /*<<< orphan*/  vexpress_restart_nb ; 
 int /*<<< orphan*/  vexpress_restart_nb_refcnt ; 

__attribute__((used)) static int _vexpress_register_restart_handler(struct device *dev)
{
	int err;

	vexpress_restart_device = dev;
	if (atomic_inc_return(&vexpress_restart_nb_refcnt) == 1) {
		err = register_restart_handler(&vexpress_restart_nb);
		if (err) {
			dev_err(dev, "cannot register restart handler (err=%d)\n", err);
			atomic_dec(&vexpress_restart_nb_refcnt);
			return err;
		}
	}
	device_create_file(dev, &dev_attr_active);

	return 0;
}