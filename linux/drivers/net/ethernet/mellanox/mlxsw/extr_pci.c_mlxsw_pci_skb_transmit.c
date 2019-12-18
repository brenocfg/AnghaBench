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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct mlxsw_tx_info {int /*<<< orphan*/  is_emad; } ;
struct TYPE_5__ {struct sk_buff* skb; } ;
struct TYPE_6__ {TYPE_1__ sdq; } ;
struct mlxsw_pci_queue_elem_info {char* elem; TYPE_2__ u; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  producer_counter; } ;
struct mlxsw_pci {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_8__ {struct mlxsw_tx_info tx_info; } ;
struct TYPE_7__ {int nr_frags; int tx_flags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int MLXSW_PCI_WQE_SG_ENTRIES ; 
 int /*<<< orphan*/  MLXSW_PCI_WQE_TYPE_ETHERNET ; 
 int SKBTX_HW_TSTAMP ; 
 int SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_producer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_producer_get (struct mlxsw_pci_queue*) ; 
 struct mlxsw_pci_queue* mlxsw_pci_sdq_pick (struct mlxsw_pci*,struct mlxsw_tx_info const*) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_byte_count_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_c_set (char*,int) ; 
 int mlxsw_pci_wqe_frag_map (struct mlxsw_pci*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_frag_unmap (struct mlxsw_pci*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_lp_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_type_set (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* mlxsw_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_frag_address (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 int skb_linearize (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlxsw_pci_skb_transmit(void *bus_priv, struct sk_buff *skb,
				  const struct mlxsw_tx_info *tx_info)
{
	struct mlxsw_pci *mlxsw_pci = bus_priv;
	struct mlxsw_pci_queue *q;
	struct mlxsw_pci_queue_elem_info *elem_info;
	char *wqe;
	int i;
	int err;

	if (skb_shinfo(skb)->nr_frags > MLXSW_PCI_WQE_SG_ENTRIES - 1) {
		err = skb_linearize(skb);
		if (err)
			return err;
	}

	q = mlxsw_pci_sdq_pick(mlxsw_pci, tx_info);
	spin_lock_bh(&q->lock);
	elem_info = mlxsw_pci_queue_elem_info_producer_get(q);
	if (!elem_info) {
		/* queue is full */
		err = -EAGAIN;
		goto unlock;
	}
	mlxsw_skb_cb(skb)->tx_info = *tx_info;
	elem_info->u.sdq.skb = skb;

	wqe = elem_info->elem;
	mlxsw_pci_wqe_c_set(wqe, 1); /* always report completion */
	mlxsw_pci_wqe_lp_set(wqe, !!tx_info->is_emad);
	mlxsw_pci_wqe_type_set(wqe, MLXSW_PCI_WQE_TYPE_ETHERNET);

	err = mlxsw_pci_wqe_frag_map(mlxsw_pci, wqe, 0, skb->data,
				     skb_headlen(skb), DMA_TO_DEVICE);
	if (err)
		goto unlock;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		err = mlxsw_pci_wqe_frag_map(mlxsw_pci, wqe, i + 1,
					     skb_frag_address(frag),
					     skb_frag_size(frag),
					     DMA_TO_DEVICE);
		if (err)
			goto unmap_frags;
	}

	if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	/* Set unused sq entries byte count to zero. */
	for (i++; i < MLXSW_PCI_WQE_SG_ENTRIES; i++)
		mlxsw_pci_wqe_byte_count_set(wqe, i, 0);

	/* Everything is set up, ring producer doorbell to get HW going */
	q->producer_counter++;
	mlxsw_pci_queue_doorbell_producer_ring(mlxsw_pci, q);

	goto unlock;

unmap_frags:
	for (; i >= 0; i--)
		mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, i, DMA_TO_DEVICE);
unlock:
	spin_unlock_bh(&q->lock);
	return err;
}