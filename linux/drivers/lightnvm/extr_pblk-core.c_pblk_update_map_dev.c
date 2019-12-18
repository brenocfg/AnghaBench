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
struct ppa_addr {int dummy; } ;
struct pblk {scalar_t__ capacity; int /*<<< orphan*/  trans_lock; int /*<<< orphan*/  padded_wb; int /*<<< orphan*/  pad_wa; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_addr_in_cache (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_map_invalidate (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_comp (struct ppa_addr,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_empty (struct ppa_addr) ; 
 struct ppa_addr pblk_trans_map_get (struct pblk*,scalar_t__) ; 
 int /*<<< orphan*/  pblk_trans_map_set (struct pblk*,scalar_t__,struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pblk_update_map_dev(struct pblk *pblk, sector_t lba,
			 struct ppa_addr ppa_mapped, struct ppa_addr ppa_cache)
{
	struct ppa_addr ppa_l2p;

#ifdef CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa points to a device address */
	BUG_ON(pblk_addr_in_cache(ppa_mapped));
#endif
	/* Invalidate and discard padded entries */
	if (lba == ADDR_EMPTY) {
		atomic64_inc(&pblk->pad_wa);
#ifdef CONFIG_NVM_PBLK_DEBUG
		atomic_long_inc(&pblk->padded_wb);
#endif
		if (!pblk_ppa_empty(ppa_mapped))
			pblk_map_invalidate(pblk, ppa_mapped);
		return;
	}

	/* logic error: lba out-of-bounds. Ignore update */
	if (!(lba < pblk->capacity)) {
		WARN(1, "pblk: corrupted L2P map request\n");
		return;
	}

	spin_lock(&pblk->trans_lock);
	ppa_l2p = pblk_trans_map_get(pblk, lba);

	/* Do not update L2P if the cacheline has been updated. In this case,
	 * the mapped ppa must be invalidated
	 */
	if (!pblk_ppa_comp(ppa_l2p, ppa_cache)) {
		if (!pblk_ppa_empty(ppa_mapped))
			pblk_map_invalidate(pblk, ppa_mapped);
		goto out;
	}

#ifdef CONFIG_NVM_PBLK_DEBUG
	WARN_ON(!pblk_addr_in_cache(ppa_l2p) && !pblk_ppa_empty(ppa_l2p));
#endif

	pblk_trans_map_set(pblk, lba, ppa_mapped);
out:
	spin_unlock(&pblk->trans_lock);
}