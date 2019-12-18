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
struct ufs_mtk_phy {void* mp_clk; void* unipro_clk; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int ufs_mtk_phy_clk_init(struct ufs_mtk_phy *phy)
{
	struct device *dev = phy->dev;

	phy->unipro_clk = devm_clk_get(dev, "unipro");
	if (IS_ERR(phy->unipro_clk)) {
		dev_err(dev, "failed to get clock: unipro");
		return PTR_ERR(phy->unipro_clk);
	}

	phy->mp_clk = devm_clk_get(dev, "mp");
	if (IS_ERR(phy->mp_clk)) {
		dev_err(dev, "failed to get clock: mp");
		return PTR_ERR(phy->mp_clk);
	}

	return 0;
}