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
struct hinic_txq {int /*<<< orphan*/  napi; TYPE_1__* sq; int /*<<< orphan*/  netdev; } ;
struct hinic_dev {int /*<<< orphan*/  hwdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  msix_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MSIX_DISABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hinic_hwdev_msix_cnt_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwdev_set_msix_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct hinic_dev* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tx_irq(int irq, void *data)
{
	struct hinic_txq *txq = data;
	struct hinic_dev *nic_dev;

	nic_dev = netdev_priv(txq->netdev);

	/* Disable the interrupt until napi will be completed */
	hinic_hwdev_set_msix_state(nic_dev->hwdev,
				   txq->sq->msix_entry,
				   HINIC_MSIX_DISABLE);

	hinic_hwdev_msix_cnt_set(nic_dev->hwdev, txq->sq->msix_entry);

	napi_schedule(&txq->napi);
	return IRQ_HANDLED;
}