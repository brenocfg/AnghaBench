#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool omap_iommu_can_register(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;

	if (!of_device_is_compatible(np, "ti,dra7-dsp-iommu"))
		return true;

	/*
	 * restrict IOMMU core registration only for processor-port MDMA MMUs
	 * on DRA7 DSPs
	 */
	if ((!strcmp(dev_name(&pdev->dev), "40d01000.mmu")) ||
	    (!strcmp(dev_name(&pdev->dev), "41501000.mmu")))
		return true;

	return false;
}