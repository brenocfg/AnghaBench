#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgbe_prv_data {scalar_t__ channel_count; TYPE_1__** channel; } ;
struct TYPE_3__ {struct TYPE_3__* tx_ring; struct TYPE_3__* rx_ring; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void xgbe_free_channels(struct xgbe_prv_data *pdata)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(pdata->channel); i++) {
		if (!pdata->channel[i])
			continue;

		kfree(pdata->channel[i]->rx_ring);
		kfree(pdata->channel[i]->tx_ring);
		kfree(pdata->channel[i]);

		pdata->channel[i] = NULL;
	}

	pdata->channel_count = 0;
}