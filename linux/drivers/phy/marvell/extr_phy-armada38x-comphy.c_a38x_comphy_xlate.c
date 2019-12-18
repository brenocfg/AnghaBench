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
typedef  int u32 ;
struct phy {int dummy; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct device {int dummy; } ;
struct a38x_comphy_lane {scalar_t__ port; int n; TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ COMPHY_SELECTOR ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 scalar_t__ MAX_A38X_PORTS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int** gbe_mux ; 
 struct phy* of_phy_simple_xlate (struct device*,struct of_phandle_args*) ; 
 struct a38x_comphy_lane* phy_get_drvdata (struct phy*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static struct phy *a38x_comphy_xlate(struct device *dev,
				     struct of_phandle_args *args)
{
	struct a38x_comphy_lane *lane;
	struct phy *phy;
	u32 val;

	if (WARN_ON(args->args[0] >= MAX_A38X_PORTS))
		return ERR_PTR(-EINVAL);

	phy = of_phy_simple_xlate(dev, args);
	if (IS_ERR(phy))
		return phy;

	lane = phy_get_drvdata(phy);
	if (lane->port >= 0)
		return ERR_PTR(-EBUSY);

	lane->port = args->args[0];

	val = readl_relaxed(lane->priv->base + COMPHY_SELECTOR);
	val = (val >> (4 * lane->n)) & 0xf;

	if (!gbe_mux[lane->n][lane->port] ||
	    val != gbe_mux[lane->n][lane->port]) {
		dev_warn(lane->priv->dev,
			 "comphy%u: not configured for GBE\n", lane->n);
		phy = ERR_PTR(-EINVAL);
	}

	return phy;
}