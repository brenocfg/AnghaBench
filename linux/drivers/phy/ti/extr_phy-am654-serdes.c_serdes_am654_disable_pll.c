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
struct serdes_am654 {int /*<<< orphan*/  pll_enable; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_DISABLE_STATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serdes_am654_disable_pll(struct serdes_am654 *phy)
{
	struct device *dev = phy->dev;
	int ret;

	ret = regmap_field_write(phy->pll_enable, PLL_DISABLE_STATE);
	if (ret)
		dev_err(dev, "Failed to disable PLL\n");
}