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
struct TYPE_2__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct syscon_reboot_context {int offset; int value; int mask; TYPE_1__ restart_handler; int /*<<< orphan*/  map; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct syscon_reboot_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int register_restart_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  syscon_restart_handle ; 

__attribute__((used)) static int syscon_reboot_probe(struct platform_device *pdev)
{
	struct syscon_reboot_context *ctx;
	struct device *dev = &pdev->dev;
	int mask_err, value_err;
	int err;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->map = syscon_regmap_lookup_by_phandle(dev->of_node, "regmap");
	if (IS_ERR(ctx->map))
		return PTR_ERR(ctx->map);

	if (of_property_read_u32(pdev->dev.of_node, "offset", &ctx->offset))
		return -EINVAL;

	value_err = of_property_read_u32(pdev->dev.of_node, "value", &ctx->value);
	mask_err = of_property_read_u32(pdev->dev.of_node, "mask", &ctx->mask);
	if (value_err && mask_err) {
		dev_err(dev, "unable to read 'value' and 'mask'");
		return -EINVAL;
	}

	if (value_err) {
		/* support old binding */
		ctx->value = ctx->mask;
		ctx->mask = 0xFFFFFFFF;
	} else if (mask_err) {
		/* support value without mask*/
		ctx->mask = 0xFFFFFFFF;
	}

	ctx->restart_handler.notifier_call = syscon_restart_handle;
	ctx->restart_handler.priority = 192;
	err = register_restart_handler(&ctx->restart_handler);
	if (err)
		dev_err(dev, "can't register restart notifier (err=%d)\n", err);

	return err;
}