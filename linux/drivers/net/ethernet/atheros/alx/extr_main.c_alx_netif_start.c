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
struct alx_priv {int num_napi; int /*<<< orphan*/  dev; TYPE_1__** qnapi; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alx_netif_start(struct alx_priv *alx)
{
	int i;

	netif_tx_wake_all_queues(alx->dev);
	for (i = 0; i < alx->num_napi; i++)
		napi_enable(&alx->qnapi[i]->napi);
	netif_carrier_on(alx->dev);
}