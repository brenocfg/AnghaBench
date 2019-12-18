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
typedef  scalar_t__ u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line {int /*<<< orphan*/  id; } ;
struct pblk {int /*<<< orphan*/  inflight_reads; } ;
struct nvm_rq {struct ppa_addr* ppa_list; } ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int NVM_MAX_VLBA ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_lookup_l2p_rand (struct pblk*,struct ppa_addr*,scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  pblk_ppa_comp (struct ppa_addr,struct ppa_addr) ; 

__attribute__((used)) static int read_ppalist_rq_gc(struct pblk *pblk, struct nvm_rq *rqd,
			      struct pblk_line *line, u64 *lba_list,
			      u64 *paddr_list_gc, unsigned int nr_secs)
{
	struct ppa_addr ppa_list_l2p[NVM_MAX_VLBA];
	struct ppa_addr ppa_gc;
	int valid_secs = 0;
	int i;

	pblk_lookup_l2p_rand(pblk, ppa_list_l2p, lba_list, nr_secs);

	for (i = 0; i < nr_secs; i++) {
		if (lba_list[i] == ADDR_EMPTY)
			continue;

		ppa_gc = addr_to_gen_ppa(pblk, paddr_list_gc[i], line->id);
		if (!pblk_ppa_comp(ppa_list_l2p[i], ppa_gc)) {
			paddr_list_gc[i] = lba_list[i] = ADDR_EMPTY;
			continue;
		}

		rqd->ppa_list[valid_secs++] = ppa_list_l2p[i];
	}

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_long_add(valid_secs, &pblk->inflight_reads);
#endif

	return valid_secs;
}