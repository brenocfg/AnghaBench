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
struct hinic_rxq {int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; struct hinic_rq* rq; } ;
struct hinic_rq {int /*<<< orphan*/  msix_entry; } ;
struct hinic_dev {int /*<<< orphan*/  hwdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MSIX_DISABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hinic_hwdev_msix_cnt_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwdev_set_msix_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct hinic_dev* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rx_irq(int irq, void *data)
{
	struct hinic_rxq *rxq = (struct hinic_rxq *)data;
	struct hinic_rq *rq = rxq->rq;
	struct hinic_dev *nic_dev;

	/* Disable the interrupt until napi will be completed */
	nic_dev = netdev_priv(rxq->netdev);
	hinic_hwdev_set_msix_state(nic_dev->hwdev,
				   rq->msix_entry,
				   HINIC_MSIX_DISABLE);

	nic_dev = netdev_priv(rxq->netdev);
	hinic_hwdev_msix_cnt_set(nic_dev->hwdev, rq->msix_entry);

	napi_schedule(&rxq->napi);
	return IRQ_HANDLED;
}