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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int of_reset_n_cells; int /*<<< orphan*/  of_xlate; struct device_node* of_node; int /*<<< orphan*/ * ops; } ;
struct hi3660_reset_controller {TYPE_1__ rst; int /*<<< orphan*/  map; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct hi3660_reset_controller* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3660_reset_ops ; 
 int /*<<< orphan*/  hi3660_reset_xlate ; 
 int reset_controller_register (TYPE_1__*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int hi3660_reset_probe(struct platform_device *pdev)
{
	struct hi3660_reset_controller *rc;
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;

	rc = devm_kzalloc(dev, sizeof(*rc), GFP_KERNEL);
	if (!rc)
		return -ENOMEM;

	rc->map = syscon_regmap_lookup_by_phandle(np, "hisi,rst-syscon");
	if (IS_ERR(rc->map)) {
		dev_err(dev, "failed to get hi3660,rst-syscon\n");
		return PTR_ERR(rc->map);
	}

	rc->rst.ops = &hi3660_reset_ops,
	rc->rst.of_node = np;
	rc->rst.of_reset_n_cells = 2;
	rc->rst.of_xlate = hi3660_reset_xlate;

	return reset_controller_register(&rc->rst);
}