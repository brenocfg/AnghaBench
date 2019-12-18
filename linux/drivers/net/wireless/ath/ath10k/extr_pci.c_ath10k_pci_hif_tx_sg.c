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
typedef  size_t u8 ;
struct ath10k_pci_pipe {struct ath10k_ce_pipe* ce_hdl; } ;
struct ath10k_pci {struct ath10k_pci_pipe* pipe_info; } ;
struct ath10k_hif_sg_item {int /*<<< orphan*/  transfer_id; int /*<<< orphan*/  len; int /*<<< orphan*/  paddr; int /*<<< orphan*/  transfer_context; int /*<<< orphan*/  vaddr; } ;
struct ath10k_ce_ring {unsigned int nentries_mask; unsigned int sw_index; unsigned int write_index; } ;
struct ath10k_ce_pipe {struct ath10k_ce_ring* src_ring; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_PCI ; 
 int /*<<< orphan*/  ATH10K_DBG_PCI_DUMP ; 
 int CE_RING_DELTA (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  CE_SEND_FLAG_GATHER ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  __ath10k_ce_send_revert (struct ath10k_ce_pipe*) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int ath10k_ce_send_nolock (struct ath10k_ce_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int ath10k_pci_hif_tx_sg(struct ath10k *ar, u8 pipe_id,
			 struct ath10k_hif_sg_item *items, int n_items)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_pci_pipe *pci_pipe = &ar_pci->pipe_info[pipe_id];
	struct ath10k_ce_pipe *ce_pipe = pci_pipe->ce_hdl;
	struct ath10k_ce_ring *src_ring = ce_pipe->src_ring;
	unsigned int nentries_mask;
	unsigned int sw_index;
	unsigned int write_index;
	int err, i = 0;

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = src_ring->nentries_mask;
	sw_index = src_ring->sw_index;
	write_index = src_ring->write_index;

	if (unlikely(CE_RING_DELTA(nentries_mask,
				   write_index, sw_index - 1) < n_items)) {
		err = -ENOBUFS;
		goto err;
	}

	for (i = 0; i < n_items - 1; i++) {
		ath10k_dbg(ar, ATH10K_DBG_PCI,
			   "pci tx item %d paddr %pad len %d n_items %d\n",
			   i, &items[i].paddr, items[i].len, n_items);
		ath10k_dbg_dump(ar, ATH10K_DBG_PCI_DUMP, NULL, "pci tx data: ",
				items[i].vaddr, items[i].len);

		err = ath10k_ce_send_nolock(ce_pipe,
					    items[i].transfer_context,
					    items[i].paddr,
					    items[i].len,
					    items[i].transfer_id,
					    CE_SEND_FLAG_GATHER);
		if (err)
			goto err;
	}

	/* `i` is equal to `n_items -1` after for() */

	ath10k_dbg(ar, ATH10K_DBG_PCI,
		   "pci tx item %d paddr %pad len %d n_items %d\n",
		   i, &items[i].paddr, items[i].len, n_items);
	ath10k_dbg_dump(ar, ATH10K_DBG_PCI_DUMP, NULL, "pci tx data: ",
			items[i].vaddr, items[i].len);

	err = ath10k_ce_send_nolock(ce_pipe,
				    items[i].transfer_context,
				    items[i].paddr,
				    items[i].len,
				    items[i].transfer_id,
				    0);
	if (err)
		goto err;

	spin_unlock_bh(&ce->ce_lock);
	return 0;

err:
	for (; i > 0; i--)
		__ath10k_ce_send_revert(ce_pipe);

	spin_unlock_bh(&ce->ce_lock);
	return err;
}