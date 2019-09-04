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
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void pblk_read_check_seq(struct pblk *pblk, struct nvm_rq *rqd,
				sector_t blba)
{
	struct pblk_sec_meta *meta_lba_list = rqd->meta_list;
	int nr_lbas = rqd->nr_ppas;
	int i;

	for (i = 0; i < nr_lbas; i++) {
		u64 lba = le64_to_cpu(meta_lba_list[i].lba);

		if (lba == ADDR_EMPTY)
			continue;

		if (lba != blba + i) {
#ifdef CONFIG_NVM_PBLK_DEBUG
			struct ppa_addr *p;

			p = (nr_lbas == 1) ? &rqd->ppa_list[i] : &rqd->ppa_addr;
			print_ppa(pblk, p, "seq", i);
#endif
			pblk_err(pblk, "corrupted read LBA (%llu/%llu)\n",
							lba, (u64)blba + i);
			WARN_ON(1);
		}
	}
}