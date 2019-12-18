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
typedef  int /*<<< orphan*/  u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line {int /*<<< orphan*/  lock; int /*<<< orphan*/  invalid_bitmap; int /*<<< orphan*/  id; } ;
struct pblk {scalar_t__ capacity; int /*<<< orphan*/  trans_lock; int /*<<< orphan*/  rwb; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_addr_in_cache (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_addr_to_cacheline (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_comp (struct ppa_addr,struct ppa_addr) ; 
 int pblk_rb_pos_oob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ppa_addr pblk_trans_map_get (struct pblk*,scalar_t__) ; 
 int /*<<< orphan*/  pblk_trans_map_set (struct pblk*,scalar_t__,struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pblk_update_map_gc(struct pblk *pblk, sector_t lba, struct ppa_addr ppa_new,
		       struct pblk_line *gc_line, u64 paddr_gc)
{
	struct ppa_addr ppa_l2p, ppa_gc;
	int ret = 1;

#ifdef CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa points to a cache address */
	BUG_ON(!pblk_addr_in_cache(ppa_new));
	BUG_ON(pblk_rb_pos_oob(&pblk->rwb, pblk_addr_to_cacheline(ppa_new)));
#endif

	/* logic error: lba out-of-bounds. Ignore update */
	if (!(lba < pblk->capacity)) {
		WARN(1, "pblk: corrupted L2P map request\n");
		return 0;
	}

	spin_lock(&pblk->trans_lock);
	ppa_l2p = pblk_trans_map_get(pblk, lba);
	ppa_gc = addr_to_gen_ppa(pblk, paddr_gc, gc_line->id);

	if (!pblk_ppa_comp(ppa_l2p, ppa_gc)) {
		spin_lock(&gc_line->lock);
		WARN(!test_bit(paddr_gc, gc_line->invalid_bitmap),
						"pblk: corrupted GC update");
		spin_unlock(&gc_line->lock);

		ret = 0;
		goto out;
	}

	pblk_trans_map_set(pblk, lba, ppa_new);
out:
	spin_unlock(&pblk->trans_lock);
	return ret;
}