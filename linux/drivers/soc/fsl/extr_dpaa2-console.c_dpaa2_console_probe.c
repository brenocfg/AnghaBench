#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__ dpaa2_aiop_console_dev ; 
 TYPE_2__ dpaa2_mc_console_dev ; 
 int /*<<< orphan*/  mc_base_addr ; 
 int /*<<< orphan*/  misc_deregister (TYPE_2__*) ; 
 int misc_register (TYPE_2__*) ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int dpaa2_console_probe(struct platform_device *pdev)
{
	int error;

	error = of_address_to_resource(pdev->dev.of_node, 0, &mc_base_addr);
	if (error < 0) {
		pr_err("of_address_to_resource() failed for %pOF with %d\n",
		       pdev->dev.of_node, error);
		return error;
	}

	error = misc_register(&dpaa2_mc_console_dev);
	if (error) {
		pr_err("cannot register device %s\n",
		       dpaa2_mc_console_dev.name);
		goto err_register_mc;
	}

	error = misc_register(&dpaa2_aiop_console_dev);
	if (error) {
		pr_err("cannot register device %s\n",
		       dpaa2_aiop_console_dev.name);
		goto err_register_aiop;
	}

	return 0;

err_register_aiop:
	misc_deregister(&dpaa2_mc_console_dev);
err_register_mc:
	return error;
}