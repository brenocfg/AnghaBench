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
struct resource {int /*<<< orphan*/  start; } ;
struct device {TYPE_1__* parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device* parent; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct aspeed_p2a_ctrl {TYPE_2__ miscdev; int /*<<< orphan*/  config; int /*<<< orphan*/  regmap; int /*<<< orphan*/  mem_base; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  tracking; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  aspeed_p2a_ctrl_fops ; 
 int /*<<< orphan*/  aspeed_p2a_disable_all (struct aspeed_p2a_ctrl*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct aspeed_p2a_ctrl*) ; 
 struct aspeed_p2a_ctrl* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int misc_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_p2a_ctrl_probe(struct platform_device *pdev)
{
	struct aspeed_p2a_ctrl *misc_ctrl;
	struct device *dev;
	struct resource resm;
	struct device_node *node;
	int rc = 0;

	dev = &pdev->dev;

	misc_ctrl = devm_kzalloc(dev, sizeof(*misc_ctrl), GFP_KERNEL);
	if (!misc_ctrl)
		return -ENOMEM;

	mutex_init(&misc_ctrl->tracking);

	/* optional. */
	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	if (node) {
		rc = of_address_to_resource(node, 0, &resm);
		of_node_put(node);
		if (rc) {
			dev_err(dev, "Couldn't address to resource for reserved memory\n");
			return -ENODEV;
		}

		misc_ctrl->mem_size = resource_size(&resm);
		misc_ctrl->mem_base = resm.start;
	}

	misc_ctrl->regmap = syscon_node_to_regmap(pdev->dev.parent->of_node);
	if (IS_ERR(misc_ctrl->regmap)) {
		dev_err(dev, "Couldn't get regmap\n");
		return -ENODEV;
	}

	misc_ctrl->config = of_device_get_match_data(dev);

	dev_set_drvdata(&pdev->dev, misc_ctrl);

	aspeed_p2a_disable_all(misc_ctrl);

	misc_ctrl->miscdev.minor = MISC_DYNAMIC_MINOR;
	misc_ctrl->miscdev.name = DEVICE_NAME;
	misc_ctrl->miscdev.fops = &aspeed_p2a_ctrl_fops;
	misc_ctrl->miscdev.parent = dev;

	rc = misc_register(&misc_ctrl->miscdev);
	if (rc)
		dev_err(dev, "Unable to register device\n");

	return rc;
}