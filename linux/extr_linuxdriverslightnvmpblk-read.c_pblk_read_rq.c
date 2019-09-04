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
struct pblk_sec_meta {void* lba; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int /*<<< orphan*/  flags; struct ppa_addr ppa_addr; struct pblk_sec_meta* meta_list; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int /*<<< orphan*/  PBLK_READ_RANDOM ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_addr_in_cache (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_lookup_l2p_seq (struct pblk*,struct ppa_addr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pblk_ppa_empty (struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_read_from_cache (struct pblk*,struct bio*,int /*<<< orphan*/ ,struct ppa_addr,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_set_read_mode (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void pblk_read_rq(struct pblk *pblk, struct nvm_rq *rqd, struct bio *bio,
			 sector_t lba, unsigned long *read_bitmap)
{
	struct pblk_sec_meta *meta_list = rqd->meta_list;
	struct ppa_addr ppa;

	pblk_lookup_l2p_seq(pblk, &ppa, lba, 1);

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_long_inc(&pblk->inflight_reads);
#endif

retry:
	if (pblk_ppa_empty(ppa)) {
		WARN_ON(test_and_set_bit(0, read_bitmap));
		meta_list[0].lba = cpu_to_le64(ADDR_EMPTY);
		return;
	}

	/* Try to read from write buffer. The address is later checked on the
	 * write buffer to prevent retrieving overwritten data.
	 */
	if (pblk_addr_in_cache(ppa)) {
		if (!pblk_read_from_cache(pblk, bio, lba, ppa, 0, 1)) {
			pblk_lookup_l2p_seq(pblk, &ppa, lba, 1);
			goto retry;
		}

		WARN_ON(test_and_set_bit(0, read_bitmap));
		meta_list[0].lba = cpu_to_le64(lba);

#ifdef CONFIG_NVM_PBLK_DEBUG
		atomic_long_inc(&pblk->cache_reads);
#endif
	} else {
		rqd->ppa_addr = ppa;
	}

	rqd->flags = pblk_set_read_mode(pblk, PBLK_READ_RANDOM);
}