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
struct xgbe_prv_data {scalar_t__ rx_pause; struct ieee_pfc* pfc; } ;
struct ieee_pfc {scalar_t__ pfc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_disable_rx_flow_control (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_rx_flow_control (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_config_rx_flow_control(struct xgbe_prv_data *pdata)
{
	struct ieee_pfc *pfc = pdata->pfc;

	if (pdata->rx_pause || (pfc && pfc->pfc_en))
		xgbe_enable_rx_flow_control(pdata);
	else
		xgbe_disable_rx_flow_control(pdata);

	return 0;
}