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
struct napi_struct {int dummy; } ;
struct xgbe_prv_data {scalar_t__ channel_irq_mode; scalar_t__ per_channel_irq; struct napi_struct napi; } ;
struct xgbe_channel {scalar_t__ tx_timer_active; int /*<<< orphan*/  dma_irq; struct napi_struct napi; struct xgbe_prv_data* pdata; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  __napi_schedule (struct napi_struct*) ; 
 struct xgbe_channel* channel ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 struct xgbe_channel* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (struct napi_struct*) ; 
 int /*<<< orphan*/  tx_timer ; 
 int /*<<< orphan*/  xgbe_disable_rx_tx_int (struct xgbe_prv_data*,struct xgbe_channel*) ; 
 int /*<<< orphan*/  xgbe_disable_rx_tx_ints (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_tx_timer(struct timer_list *t)
{
	struct xgbe_channel *channel = from_timer(channel, t, tx_timer);
	struct xgbe_prv_data *pdata = channel->pdata;
	struct napi_struct *napi;

	DBGPR("-->xgbe_tx_timer\n");

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	if (napi_schedule_prep(napi)) {
		/* Disable Tx and Rx interrupts */
		if (pdata->per_channel_irq)
			if (pdata->channel_irq_mode)
				xgbe_disable_rx_tx_int(pdata, channel);
			else
				disable_irq_nosync(channel->dma_irq);
		else
			xgbe_disable_rx_tx_ints(pdata);

		/* Turn on polling */
		__napi_schedule(napi);
	}

	channel->tx_timer_active = 0;

	DBGPR("<--xgbe_tx_timer\n");
}