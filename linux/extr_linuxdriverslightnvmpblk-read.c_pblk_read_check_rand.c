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
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int nr_ppas; struct pblk_sec_meta* meta_list; } ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void pblk_read_check_rand(struct pblk *pblk, struct nvm_rq *rqd,
				 u64 *lba_list, int nr_lbas)
{
	struct pblk_sec_meta *meta_lba_list = rqd->meta_list;
	int i, j;

	for (i = 0, j = 0; i < nr_lbas; i++) {
		u64 lba = lba_list[i];
		u64 meta_lba;

		if (lba == ADDR_EMPTY)
			continue;

		meta_lba = le64_to_cpu(meta_lba_list[j].lba);

		if (lba != meta_lba) {
#ifdef CONFIG_NVM_PBLK_DEBUG
			struct ppa_addr *p;
			int nr_ppas = rqd->nr_ppas;

			p = (nr_ppas == 1) ? &rqd->ppa_list[j] : &rqd->ppa_addr;
			print_ppa(pblk, p, "seq", j);
#endif
			pblk_err(pblk, "corrupted read LBA (%llu/%llu)\n",
								lba, meta_lba);
			WARN_ON(1);
		}

		j++;
	}

	WARN_ONCE(j != rqd->nr_ppas, "pblk: corrupted random request\n");
}