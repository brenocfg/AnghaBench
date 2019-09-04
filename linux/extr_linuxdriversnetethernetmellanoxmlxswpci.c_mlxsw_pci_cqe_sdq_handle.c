#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct sk_buff* skb; } ;
struct TYPE_4__ {TYPE_1__ sdq; } ;
struct mlxsw_pci_queue_elem_info {char* elem; TYPE_2__ u; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  consumer_counter; } ;
struct mlxsw_pci {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MLXSW_PCI_WQE_SG_ENTRIES ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_consumer_get (struct mlxsw_pci_queue*) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_frag_unmap (struct mlxsw_pci*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_pci_cqe_sdq_handle(struct mlxsw_pci *mlxsw_pci,
				     struct mlxsw_pci_queue *q,
				     u16 consumer_counter_limit,
				     char *cqe)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;
	struct mlxsw_pci_queue_elem_info *elem_info;
	char *wqe;
	struct sk_buff *skb;
	int i;

	spin_lock(&q->lock);
	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	skb = elem_info->u.sdq.skb;
	wqe = elem_info->elem;
	for (i = 0; i < MLXSW_PCI_WQE_SG_ENTRIES; i++)
		mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, i, DMA_TO_DEVICE);
	dev_kfree_skb_any(skb);
	elem_info->u.sdq.skb = NULL;

	if (q->consumer_counter++ != consumer_counter_limit)
		dev_dbg_ratelimited(&pdev->dev, "Consumer counter does not match limit in SDQ\n");
	spin_unlock(&q->lock);
}