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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_ahb {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regs; } ;
struct resource {int start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INCORRECT_BASE_ADDR_LOW_BYTE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_ahb* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_ahb*) ; 
 int /*<<< orphan*/  tegra_ahb_gizmo ; 
 int /*<<< orphan*/  tegra_ahb_gizmo_init (struct tegra_ahb*) ; 

__attribute__((used)) static int tegra_ahb_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct tegra_ahb *ahb;
	size_t bytes;

	bytes = sizeof(*ahb) + sizeof(u32) * ARRAY_SIZE(tegra_ahb_gizmo);
	ahb = devm_kzalloc(&pdev->dev, bytes, GFP_KERNEL);
	if (!ahb)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	/* Correct the IP block base address if necessary */
	if (res &&
	    (res->start & INCORRECT_BASE_ADDR_LOW_BYTE) ==
	    INCORRECT_BASE_ADDR_LOW_BYTE) {
		dev_warn(&pdev->dev, "incorrect AHB base address in DT data - enabling workaround\n");
		res->start -= INCORRECT_BASE_ADDR_LOW_BYTE;
	}

	ahb->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ahb->regs))
		return PTR_ERR(ahb->regs);

	ahb->dev = &pdev->dev;
	platform_set_drvdata(pdev, ahb);
	tegra_ahb_gizmo_init(ahb);
	return 0;
}