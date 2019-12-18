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
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int nr_ppas; void* meta_list; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,scalar_t__,scalar_t__) ; 
 struct pblk_sec_meta* pblk_get_meta (struct pblk*,void*,int) ; 
 int /*<<< orphan*/  pblk_is_oob_meta_supported (struct pblk*) ; 
 int /*<<< orphan*/  print_ppa (struct pblk*,struct ppa_addr*,char*,int) ; 

__attribute__((used)) static void pblk_read_check_seq(struct pblk *pblk, struct nvm_rq *rqd,
				sector_t blba)
{
	void *meta_list = rqd->meta_list;
	int nr_lbas = rqd->nr_ppas;
	int i;

	if (!pblk_is_oob_meta_supported(pblk))
		return;

	for (i = 0; i < nr_lbas; i++) {
		struct pblk_sec_meta *meta = pblk_get_meta(pblk, meta_list, i);
		u64 lba = le64_to_cpu(meta->lba);

		if (lba == ADDR_EMPTY)
			continue;

		if (lba != blba + i) {
#ifdef CONFIG_NVM_PBLK_DEBUG
			struct ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

			print_ppa(pblk, &ppa_list[i], "seq", i);
#endif
			pblk_err(pblk, "corrupted read LBA (%llu/%llu)\n",
							lba, (u64)blba + i);
			WARN_ON(1);
		}
	}
}