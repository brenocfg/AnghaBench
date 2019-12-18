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
struct orion_mdio_dev {scalar_t__ err_interrupt; int /*<<< orphan*/ * clk; scalar_t__ regs; } ;
struct mii_bus {struct orion_mdio_dev* priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MVMDIO_ERR_INT_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct mii_bus* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int orion_mdio_remove(struct platform_device *pdev)
{
	struct mii_bus *bus = platform_get_drvdata(pdev);
	struct orion_mdio_dev *dev = bus->priv;
	int i;

	if (dev->err_interrupt > 0)
		writel(0, dev->regs + MVMDIO_ERR_INT_MASK);
	mdiobus_unregister(bus);

	for (i = 0; i < ARRAY_SIZE(dev->clk); i++) {
		if (IS_ERR(dev->clk[i]))
			break;
		clk_disable_unprepare(dev->clk[i]);
		clk_put(dev->clk[i]);
	}

	return 0;
}