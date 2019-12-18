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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_nand_info {int /*<<< orphan*/ * elm_dev; TYPE_1__* pdev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 

__attribute__((used)) static bool is_elm_present(struct omap_nand_info *info,
			   struct device_node *elm_node)
{
	struct platform_device *pdev;

	/* check whether elm-id is passed via DT */
	if (!elm_node) {
		dev_err(&info->pdev->dev, "ELM devicetree node not found\n");
		return false;
	}
	pdev = of_find_device_by_node(elm_node);
	/* check whether ELM device is registered */
	if (!pdev) {
		dev_err(&info->pdev->dev, "ELM device not found\n");
		return false;
	}
	/* ELM module available, now configure it */
	info->elm_dev = &pdev->dev;
	return true;
}