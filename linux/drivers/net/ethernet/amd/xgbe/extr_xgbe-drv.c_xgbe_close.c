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
struct xgbe_prv_data {int /*<<< orphan*/  dev_state; int /*<<< orphan*/  dev_workqueue; int /*<<< orphan*/  an_workqueue; int /*<<< orphan*/  sysclk; int /*<<< orphan*/  ptpclk; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_DOWN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_free_memory (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_stop (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_close(struct net_device *netdev)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	/* Stop the device */
	xgbe_stop(pdata);

	xgbe_free_memory(pdata);

	/* Disable the clocks */
	clk_disable_unprepare(pdata->ptpclk);
	clk_disable_unprepare(pdata->sysclk);

	flush_workqueue(pdata->an_workqueue);
	destroy_workqueue(pdata->an_workqueue);

	flush_workqueue(pdata->dev_workqueue);
	destroy_workqueue(pdata->dev_workqueue);

	set_bit(XGBE_DOWN, &pdata->dev_state);

	return 0;
}