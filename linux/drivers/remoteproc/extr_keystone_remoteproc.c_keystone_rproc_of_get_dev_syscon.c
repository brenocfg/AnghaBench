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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct keystone_rproc {int /*<<< orphan*/  boot_offset; int /*<<< orphan*/  dev_ctrl; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int keystone_rproc_of_get_dev_syscon(struct platform_device *pdev,
					    struct keystone_rproc *ksproc)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	int ret;

	if (!of_property_read_bool(np, "ti,syscon-dev")) {
		dev_err(dev, "ti,syscon-dev property is absent\n");
		return -EINVAL;
	}

	ksproc->dev_ctrl =
		syscon_regmap_lookup_by_phandle(np, "ti,syscon-dev");
	if (IS_ERR(ksproc->dev_ctrl)) {
		ret = PTR_ERR(ksproc->dev_ctrl);
		return ret;
	}

	if (of_property_read_u32_index(np, "ti,syscon-dev", 1,
				       &ksproc->boot_offset)) {
		dev_err(dev, "couldn't read the boot register offset\n");
		return -EINVAL;
	}

	return 0;
}