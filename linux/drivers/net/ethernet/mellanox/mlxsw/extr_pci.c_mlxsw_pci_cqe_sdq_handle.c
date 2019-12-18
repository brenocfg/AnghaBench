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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mlxsw_tx_info {int /*<<< orphan*/  local_port; int /*<<< orphan*/  is_emad; } ;
struct TYPE_5__ {struct sk_buff* skb; } ;
struct TYPE_6__ {TYPE_1__ sdq; } ;
struct mlxsw_pci_queue_elem_info {char* elem; TYPE_2__ u; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  consumer_counter; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; struct pci_dev* pdev; } ;
struct TYPE_8__ {struct mlxsw_tx_info tx_info; } ;
struct TYPE_7__ {int tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MLXSW_PCI_WQE_SG_ENTRIES ; 
 int SKBTX_HW_TSTAMP ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  mlxsw_core_ptp_transmitted (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_consumer_get (struct mlxsw_pci_queue*) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_frag_unmap (struct mlxsw_pci*,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* mlxsw_skb_cb (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlxsw_pci_cqe_sdq_handle(struct mlxsw_pci *mlxsw_pci,
				     struct mlxsw_pci_queue *q,
				     u16 consumer_counter_limit,
				     char *cqe)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;
	struct mlxsw_pci_queue_elem_info *elem_info;
	struct mlxsw_tx_info tx_info;
	char *wqe;
	struct sk_buff *skb;
	int i;

	spin_lock(&q->lock);
	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	tx_info = mlxsw_skb_cb(elem_info->u.sdq.skb)->tx_info;
	skb = elem_info->u.sdq.skb;
	wqe = elem_info->elem;
	for (i = 0; i < MLXSW_PCI_WQE_SG_ENTRIES; i++)
		mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, i, DMA_TO_DEVICE);

	if (unlikely(!tx_info.is_emad &&
		     skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) {
		mlxsw_core_ptp_transmitted(mlxsw_pci->core, skb,
					   tx_info.local_port);
		skb = NULL;
	}

	if (skb)
		dev_kfree_skb_any(skb);
	elem_info->u.sdq.skb = NULL;

	if (q->consumer_counter++ != consumer_counter_limit)
		dev_dbg_ratelimited(&pdev->dev, "Consumer counter does not match limit in SDQ\n");
	spin_unlock(&q->lock);
}