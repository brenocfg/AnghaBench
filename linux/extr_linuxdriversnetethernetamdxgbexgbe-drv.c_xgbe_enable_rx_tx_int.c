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
struct xgbe_hw_if {int /*<<< orphan*/  (* enable_int ) (struct xgbe_channel*,int) ;} ;
struct xgbe_prv_data {struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {scalar_t__ rx_ring; scalar_t__ tx_ring; } ;
typedef  enum xgbe_int { ____Placeholder_xgbe_int } xgbe_int ;

/* Variables and functions */
 int XGMAC_INT_DMA_CH_SR_RI ; 
 int XGMAC_INT_DMA_CH_SR_TI ; 
 int XGMAC_INT_DMA_CH_SR_TI_RI ; 
 int /*<<< orphan*/  stub1 (struct xgbe_channel*,int) ; 

__attribute__((used)) static void xgbe_enable_rx_tx_int(struct xgbe_prv_data *pdata,
				  struct xgbe_channel *channel)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	enum xgbe_int int_id;

	if (channel->tx_ring && channel->rx_ring)
		int_id = XGMAC_INT_DMA_CH_SR_TI_RI;
	else if (channel->tx_ring)
		int_id = XGMAC_INT_DMA_CH_SR_TI;
	else if (channel->rx_ring)
		int_id = XGMAC_INT_DMA_CH_SR_RI;
	else
		return;

	hw_if->enable_int(channel, int_id);
}