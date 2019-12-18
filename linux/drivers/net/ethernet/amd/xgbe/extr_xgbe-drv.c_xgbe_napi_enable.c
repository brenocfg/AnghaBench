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
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; struct xgbe_channel** channel; scalar_t__ per_channel_irq; } ;
struct xgbe_channel {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_all_poll ; 
 int /*<<< orphan*/  xgbe_one_poll ; 

__attribute__((used)) static void xgbe_napi_enable(struct xgbe_prv_data *pdata, unsigned int add)
{
	struct xgbe_channel *channel;
	unsigned int i;

	if (pdata->per_channel_irq) {
		for (i = 0; i < pdata->channel_count; i++) {
			channel = pdata->channel[i];
			if (add)
				netif_napi_add(pdata->netdev, &channel->napi,
					       xgbe_one_poll, NAPI_POLL_WEIGHT);

			napi_enable(&channel->napi);
		}
	} else {
		if (add)
			netif_napi_add(pdata->netdev, &pdata->napi,
				       xgbe_all_poll, NAPI_POLL_WEIGHT);

		napi_enable(&pdata->napi);
	}
}