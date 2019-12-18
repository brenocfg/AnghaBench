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
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xgbe_an37_disable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an37_set (struct xgbe_prv_data*,int,int) ; 

__attribute__((used)) static void xgbe_an37_disable(struct xgbe_prv_data *pdata)
{
	xgbe_an37_set(pdata, false, false);
	xgbe_an37_disable_interrupts(pdata);

	netif_dbg(pdata, link, pdata->netdev, "CL37 AN disabled\n");
}