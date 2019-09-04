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
struct alx_priv {int num_napi; TYPE_1__** qnapi; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alx_netif_stop(struct alx_priv *alx)
{
	int i;

	netif_trans_update(alx->dev);
	if (netif_carrier_ok(alx->dev)) {
		netif_carrier_off(alx->dev);
		netif_tx_disable(alx->dev);
		for (i = 0; i < alx->num_napi; i++)
			napi_disable(&alx->qnapi[i]->napi);
	}
}