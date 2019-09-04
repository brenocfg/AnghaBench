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
struct platform_device {int dummy; } ;
struct pcie_gadget_target {int /*<<< orphan*/  subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_unregister_subsystem (int /*<<< orphan*/ *) ; 
 struct pcie_gadget_target* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int spear_pcie_gadget_remove(struct platform_device *pdev)
{
	static struct pcie_gadget_target *target;

	target = platform_get_drvdata(pdev);

	configfs_unregister_subsystem(&target->subsys);

	return 0;
}