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
struct phy {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN_ONCE (struct device*,int,char*) ; 
 int /*<<< orphan*/  devm_phy_match ; 
 int /*<<< orphan*/  devm_phy_release ; 
 int devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct phy*) ; 

void devm_phy_put(struct device *dev, struct phy *phy)
{
	int r;

	if (!phy)
		return;

	r = devres_destroy(dev, devm_phy_release, devm_phy_match, phy);
	dev_WARN_ONCE(dev, r, "couldn't find PHY resource\n");
}