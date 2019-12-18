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
struct xlgmac_pdata {scalar_t__ channel_count; TYPE_1__* channel_head; } ;
struct TYPE_2__ {struct TYPE_2__* rx_ring; struct TYPE_2__* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void xlgmac_free_channels(struct xlgmac_pdata *pdata)
{
	if (!pdata->channel_head)
		return;

	kfree(pdata->channel_head->tx_ring);
	pdata->channel_head->tx_ring = NULL;

	kfree(pdata->channel_head->rx_ring);
	pdata->channel_head->rx_ring = NULL;

	kfree(pdata->channel_head);

	pdata->channel_head = NULL;
	pdata->channel_count = 0;
}