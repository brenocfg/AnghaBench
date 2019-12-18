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
struct hinic_txq {int /*<<< orphan*/  sges; int /*<<< orphan*/  free_sges; int /*<<< orphan*/  irq_name; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_all_tx_skbs (struct hinic_txq*) ; 
 int /*<<< orphan*/  tx_free_irq (struct hinic_txq*) ; 

void hinic_clean_txq(struct hinic_txq *txq)
{
	struct net_device *netdev = txq->netdev;

	tx_free_irq(txq);

	free_all_tx_skbs(txq);

	devm_kfree(&netdev->dev, txq->irq_name);
	devm_kfree(&netdev->dev, txq->free_sges);
	devm_kfree(&netdev->dev, txq->sges);
}