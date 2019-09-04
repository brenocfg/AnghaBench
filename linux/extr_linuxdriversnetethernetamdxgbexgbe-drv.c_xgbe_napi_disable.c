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
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/  napi; struct xgbe_channel** channel; scalar_t__ per_channel_irq; } ;
struct xgbe_channel {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_napi_disable(struct xgbe_prv_data *pdata, unsigned int del)
{
	struct xgbe_channel *channel;
	unsigned int i;

	if (pdata->per_channel_irq) {
		for (i = 0; i < pdata->channel_count; i++) {
			channel = pdata->channel[i];
			napi_disable(&channel->napi);

			if (del)
				netif_napi_del(&channel->napi);
		}
	} else {
		napi_disable(&pdata->napi);

		if (del)
			netif_napi_del(&pdata->napi);
	}
}