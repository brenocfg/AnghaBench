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
struct pblk {int /*<<< orphan*/  trans_lock; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_addr_in_cache (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_map_invalidate (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_empty (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_set_empty (struct ppa_addr*) ; 
 struct ppa_addr pblk_trans_map_get (struct pblk*,scalar_t__) ; 
 int /*<<< orphan*/  pblk_trans_map_set (struct pblk*,scalar_t__,struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_invalidate_range(struct pblk *pblk, sector_t slba,
				  unsigned int nr_secs)
{
	sector_t lba;

	spin_lock(&pblk->trans_lock);
	for (lba = slba; lba < slba + nr_secs; lba++) {
		struct ppa_addr ppa;

		ppa = pblk_trans_map_get(pblk, lba);

		if (!pblk_addr_in_cache(ppa) && !pblk_ppa_empty(ppa))
			pblk_map_invalidate(pblk, ppa);

		pblk_ppa_set_empty(&ppa);
		pblk_trans_map_set(pblk, lba, ppa);
	}
	spin_unlock(&pblk->trans_lock);
}