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
struct net_device {int /*<<< orphan*/  dev; } ;
struct hinic_rxq {int /*<<< orphan*/  irq_name; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_all_rx_skbs (struct hinic_rxq*) ; 
 int /*<<< orphan*/  rx_free_irq (struct hinic_rxq*) ; 

void hinic_clean_rxq(struct hinic_rxq *rxq)
{
	struct net_device *netdev = rxq->netdev;

	rx_free_irq(rxq);

	free_all_rx_skbs(rxq);
	devm_kfree(&netdev->dev, rxq->irq_name);
}