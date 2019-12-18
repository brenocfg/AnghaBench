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
struct gb_module {size_t num_interfaces; int /*<<< orphan*/ * interfaces; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_module_register_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_module_add (struct gb_module*) ; 

int gb_module_add(struct gb_module *module)
{
	size_t i;
	int ret;

	ret = device_add(&module->dev);
	if (ret) {
		dev_err(&module->dev, "failed to register module: %d\n", ret);
		return ret;
	}

	trace_gb_module_add(module);

	for (i = 0; i < module->num_interfaces; ++i)
		gb_module_register_interface(module->interfaces[i]);

	return 0;
}