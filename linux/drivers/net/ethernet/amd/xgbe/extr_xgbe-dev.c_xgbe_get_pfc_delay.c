#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xgbe_prv_data {TYPE_1__* pfc; } ;
struct TYPE_2__ {int delay; } ;

/* Variables and functions */
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ XGMAC_ETH_PREAMBLE ; 
 scalar_t__ XGMAC_PFC_DATA_LEN ; 
 scalar_t__ XGMAC_PFC_DELAYS ; 
 unsigned int xgbe_get_max_frame (struct xgbe_prv_data*) ; 

__attribute__((used)) static unsigned int xgbe_get_pfc_delay(struct xgbe_prv_data *pdata)
{
	unsigned int delay;

	/* If a delay has been provided, use that */
	if (pdata->pfc->delay)
		return pdata->pfc->delay / 8;

	/* Allow for two maximum size frames */
	delay = xgbe_get_max_frame(pdata);
	delay += XGMAC_ETH_PREAMBLE;
	delay *= 2;

	/* Allow for PFC frame */
	delay += XGMAC_PFC_DATA_LEN;
	delay += ETH_HLEN + ETH_FCS_LEN;
	delay += XGMAC_ETH_PREAMBLE;

	/* Allow for miscellaneous delays (LPI exit, cable, etc.) */
	delay += XGMAC_PFC_DELAYS;

	return delay;
}