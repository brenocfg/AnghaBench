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
struct hinic_txq {int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_tx_poll ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tx_napi_add(struct hinic_txq *txq, int weight)
{
	netif_napi_add(txq->netdev, &txq->napi, free_tx_poll, weight);
	napi_enable(&txq->napi);
}