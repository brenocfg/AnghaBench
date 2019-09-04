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
struct hinic_rxq {int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; } ;
struct hinic_dev {int /*<<< orphan*/  rx_weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct hinic_dev* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_poll ; 

__attribute__((used)) static void rx_add_napi(struct hinic_rxq *rxq)
{
	struct hinic_dev *nic_dev = netdev_priv(rxq->netdev);

	netif_napi_add(rxq->netdev, &rxq->napi, rx_poll, nic_dev->rx_weight);
	napi_enable(&rxq->napi);
}