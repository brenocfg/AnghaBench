#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mvebu_icu {scalar_t__ base; TYPE_1__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICU_GROUP_SHIFT ; 
 int ICU_GRP_NSR ; 
 int ICU_GRP_SEI ; 
 scalar_t__ ICU_INT_CFG (int) ; 
 int ICU_MAX_IRQS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mvebu_icu* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (TYPE_1__*) ; 
 int /*<<< orphan*/  legacy_bindings ; 
 int mvebu_icu_subset_probe (struct platform_device*) ; 
 int /*<<< orphan*/  of_get_child_count (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mvebu_icu*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int mvebu_icu_probe(struct platform_device *pdev)
{
	struct mvebu_icu *icu;
	struct resource *res;
	int i;

	icu = devm_kzalloc(&pdev->dev, sizeof(struct mvebu_icu),
			   GFP_KERNEL);
	if (!icu)
		return -ENOMEM;

	icu->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	icu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(icu->base)) {
		dev_err(&pdev->dev, "Failed to map icu base address.\n");
		return PTR_ERR(icu->base);
	}

	/*
	 * Legacy bindings: ICU is one node with one MSI parent: force manually
	 *                  the probe of the NSR interrupts side.
	 * New bindings: ICU node has children, one per interrupt controller
	 *               having its own MSI parent: call platform_populate().
	 * All ICU instances should use the same bindings.
	 */
	if (!of_get_child_count(pdev->dev.of_node))
		static_branch_enable(&legacy_bindings);

	/*
	 * Clean all ICU interrupts of type NSR and SEI, required to
	 * avoid unpredictable SPI assignments done by firmware.
	 */
	for (i = 0 ; i < ICU_MAX_IRQS ; i++) {
		u32 icu_int, icu_grp;

		icu_int = readl_relaxed(icu->base + ICU_INT_CFG(i));
		icu_grp = icu_int >> ICU_GROUP_SHIFT;

		if (icu_grp == ICU_GRP_NSR ||
		    (icu_grp == ICU_GRP_SEI &&
		     !static_branch_unlikely(&legacy_bindings)))
			writel_relaxed(0x0, icu->base + ICU_INT_CFG(i));
	}

	platform_set_drvdata(pdev, icu);

	if (static_branch_unlikely(&legacy_bindings))
		return mvebu_icu_subset_probe(pdev);
	else
		return devm_of_platform_populate(&pdev->dev);
}