#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xgene_enet_pdata {int rxq_cnt; int cq_cnt; int /*<<< orphan*/  ndev; TYPE_2__** tx_ring; TYPE_3__** rx_ring; } ;
struct napi_struct {int dummy; } ;
struct TYPE_6__ {struct napi_struct napi; } ;
struct TYPE_5__ {TYPE_1__* cp_ring; } ;
struct TYPE_4__ {struct napi_struct napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,struct napi_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_napi ; 

__attribute__((used)) static void xgene_enet_napi_add(struct xgene_enet_pdata *pdata)
{
	struct napi_struct *napi;
	int i;

	for (i = 0; i < pdata->rxq_cnt; i++) {
		napi = &pdata->rx_ring[i]->napi;
		netif_napi_add(pdata->ndev, napi, xgene_enet_napi,
			       NAPI_POLL_WEIGHT);
	}

	for (i = 0; i < pdata->cq_cnt; i++) {
		napi = &pdata->tx_ring[i]->cp_ring->napi;
		netif_napi_add(pdata->ndev, napi, xgene_enet_napi,
			       NAPI_POLL_WEIGHT);
	}
}