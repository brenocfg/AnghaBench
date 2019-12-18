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
struct xgbe_prv_data {struct platform_device* platdev; int /*<<< orphan*/  dev; scalar_t__ use_acpi; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ ) ; 
 struct platform_device* xgbe_of_get_phy_pdev (struct xgbe_prv_data*) ; 

__attribute__((used)) static struct platform_device *xgbe_get_phy_pdev(struct xgbe_prv_data *pdata)
{
	struct platform_device *phy_pdev;

	if (pdata->use_acpi) {
		get_device(pdata->dev);
		phy_pdev = pdata->platdev;
	} else {
		phy_pdev = xgbe_of_get_phy_pdev(pdata);
	}

	return phy_pdev;
}