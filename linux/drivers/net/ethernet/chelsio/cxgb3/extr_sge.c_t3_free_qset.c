#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tx_desc {int dummy; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  phys_addr; scalar_t__ desc; int /*<<< orphan*/  cntxt_id; } ;
struct sge_qset {TYPE_2__ rspq; TYPE_3__* txq; TYPE_4__* fl; } ;
struct rx_desc {int dummy; } ;
struct rsp_desc {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg_lock; } ;
struct adapter {TYPE_1__ sge; struct pci_dev* pdev; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  phys_addr; scalar_t__ desc; scalar_t__ sdesc; int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  sendq; int /*<<< orphan*/  phys_addr; scalar_t__ desc; scalar_t__ sdesc; int /*<<< orphan*/  in_use; int /*<<< orphan*/  cntxt_id; } ;

/* Variables and functions */
 int SGE_RXQ_PER_SET ; 
 int SGE_TXQ_PER_SET ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rx_bufs (struct pci_dev*,TYPE_4__*) ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_reset_qset (struct sge_qset*) ; 
 int /*<<< orphan*/  t3_sge_disable_fl (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_sge_disable_rspcntxt (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_sge_enable_ecntxt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t3_free_qset(struct adapter *adapter, struct sge_qset *q)
{
	int i;
	struct pci_dev *pdev = adapter->pdev;

	for (i = 0; i < SGE_RXQ_PER_SET; ++i)
		if (q->fl[i].desc) {
			spin_lock_irq(&adapter->sge.reg_lock);
			t3_sge_disable_fl(adapter, q->fl[i].cntxt_id);
			spin_unlock_irq(&adapter->sge.reg_lock);
			free_rx_bufs(pdev, &q->fl[i]);
			kfree(q->fl[i].sdesc);
			dma_free_coherent(&pdev->dev,
					  q->fl[i].size *
					  sizeof(struct rx_desc), q->fl[i].desc,
					  q->fl[i].phys_addr);
		}

	for (i = 0; i < SGE_TXQ_PER_SET; ++i)
		if (q->txq[i].desc) {
			spin_lock_irq(&adapter->sge.reg_lock);
			t3_sge_enable_ecntxt(adapter, q->txq[i].cntxt_id, 0);
			spin_unlock_irq(&adapter->sge.reg_lock);
			if (q->txq[i].sdesc) {
				free_tx_desc(adapter, &q->txq[i],
					     q->txq[i].in_use);
				kfree(q->txq[i].sdesc);
			}
			dma_free_coherent(&pdev->dev,
					  q->txq[i].size *
					  sizeof(struct tx_desc),
					  q->txq[i].desc, q->txq[i].phys_addr);
			__skb_queue_purge(&q->txq[i].sendq);
		}

	if (q->rspq.desc) {
		spin_lock_irq(&adapter->sge.reg_lock);
		t3_sge_disable_rspcntxt(adapter, q->rspq.cntxt_id);
		spin_unlock_irq(&adapter->sge.reg_lock);
		dma_free_coherent(&pdev->dev,
				  q->rspq.size * sizeof(struct rsp_desc),
				  q->rspq.desc, q->rspq.phys_addr);
	}

	t3_reset_qset(q);
}