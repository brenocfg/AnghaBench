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
struct serdes_am654 {int busy; int /*<<< orphan*/  type; int /*<<< orphan*/  control; } ;
struct phy {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct phy* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int mux_control_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy* of_phy_simple_xlate (struct device*,struct of_phandle_args*) ; 
 struct serdes_am654* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static struct phy *serdes_am654_xlate(struct device *dev,
				      struct of_phandle_args *args)
{
	struct serdes_am654 *am654_phy;
	struct phy *phy;
	int ret;

	phy = of_phy_simple_xlate(dev, args);
	if (IS_ERR(phy))
		return phy;

	am654_phy = phy_get_drvdata(phy);
	if (am654_phy->busy)
		return ERR_PTR(-EBUSY);

	ret = mux_control_select(am654_phy->control, args->args[1]);
	if (ret) {
		dev_err(dev, "Failed to select SERDES Lane Function\n");
		return ERR_PTR(ret);
	}

	am654_phy->busy = true;
	am654_phy->type = args->args[0];

	return phy;
}