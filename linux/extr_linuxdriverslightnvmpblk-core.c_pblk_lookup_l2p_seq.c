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
struct pblk_line {int /*<<< orphan*/  ref; } ;
struct pblk {int /*<<< orphan*/  trans_lock; struct pblk_line* lines; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_addr_in_cache (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_ppa_empty (struct ppa_addr) ; 
 int pblk_ppa_to_line (struct ppa_addr) ; 
 struct ppa_addr pblk_trans_map_get (struct pblk*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pblk_lookup_l2p_seq(struct pblk *pblk, struct ppa_addr *ppas,
			 sector_t blba, int nr_secs)
{
	int i;

	spin_lock(&pblk->trans_lock);
	for (i = 0; i < nr_secs; i++) {
		struct ppa_addr ppa;

		ppa = ppas[i] = pblk_trans_map_get(pblk, blba + i);

		/* If the L2P entry maps to a line, the reference is valid */
		if (!pblk_ppa_empty(ppa) && !pblk_addr_in_cache(ppa)) {
			int line_id = pblk_ppa_to_line(ppa);
			struct pblk_line *line = &pblk->lines[line_id];

			kref_get(&line->ref);
		}
	}
	spin_unlock(&pblk->trans_lock);
}