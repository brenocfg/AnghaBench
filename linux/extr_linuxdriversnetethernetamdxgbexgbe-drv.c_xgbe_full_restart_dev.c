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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_alloc_memory (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_free_memory (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_start (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_stop (struct xgbe_prv_data*) ; 

void xgbe_full_restart_dev(struct xgbe_prv_data *pdata)
{
	/* If not running, "restart" will happen on open */
	if (!netif_running(pdata->netdev))
		return;

	xgbe_stop(pdata);

	xgbe_free_memory(pdata);
	xgbe_alloc_memory(pdata);

	xgbe_start(pdata);
}