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
struct xgbe_prv_data {int /*<<< orphan*/  phy_platdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xgbe_deconfig_netdev (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_free_pdata (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_platform_remove(struct platform_device *pdev)
{
	struct xgbe_prv_data *pdata = platform_get_drvdata(pdev);

	xgbe_deconfig_netdev(pdata);

	platform_device_put(pdata->phy_platdev);

	xgbe_free_pdata(pdata);

	return 0;
}