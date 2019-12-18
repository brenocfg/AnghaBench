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
struct rk_priv_data {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rk_priv_data* get_stmmac_bsp_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_gmac_powerdown (struct rk_priv_data*) ; 
 int stmmac_dvr_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_gmac_remove(struct platform_device *pdev)
{
	struct rk_priv_data *bsp_priv = get_stmmac_bsp_priv(&pdev->dev);
	int ret = stmmac_dvr_remove(&pdev->dev);

	rk_gmac_powerdown(bsp_priv);

	return ret;
}