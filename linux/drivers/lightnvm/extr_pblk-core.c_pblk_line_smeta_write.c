#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct pblk_line_meta {int smeta_sec; } ;
struct pblk_line {int /*<<< orphan*/  smeta; int /*<<< orphan*/  id; TYPE_1__* emeta; } ;
struct pblk {int /*<<< orphan*/  inflight_io; struct pblk_line_meta lm; } ;
struct nvm_rq {int nr_ppas; int is_seq; scalar_t__ error; int /*<<< orphan*/  meta_list; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int EIO ; 
 int /*<<< orphan*/  NVM_OP_PWRITE ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 int pblk_alloc_rqd_meta (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_free_rqd_meta (struct pblk*,struct nvm_rq*) ; 
 struct pblk_sec_meta* pblk_get_meta (struct pblk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_log_write_err (struct pblk*,struct nvm_rq*) ; 
 int pblk_submit_io_sync_sem (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_line_smeta_write(struct pblk *pblk, struct pblk_line *line,
				 u64 paddr)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct ppa_addr *ppa_list;
	struct nvm_rq rqd;
	__le64 *lba_list = emeta_to_lbas(pblk, line->emeta->buf);
	__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);
	int i, ret;

	memset(&rqd, 0, sizeof(struct nvm_rq));

	ret = pblk_alloc_rqd_meta(pblk, &rqd);
	if (ret)
		return ret;

	rqd.opcode = NVM_OP_PWRITE;
	rqd.nr_ppas = lm->smeta_sec;
	rqd.is_seq = 1;
	ppa_list = nvm_rq_to_ppa_list(&rqd);

	for (i = 0; i < lm->smeta_sec; i++, paddr++) {
		struct pblk_sec_meta *meta = pblk_get_meta(pblk,
							   rqd.meta_list, i);

		ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);
		meta->lba = lba_list[paddr] = addr_empty;
	}

	ret = pblk_submit_io_sync_sem(pblk, &rqd, line->smeta);
	if (ret) {
		pblk_err(pblk, "smeta I/O submission failed: %d\n", ret);
		goto clear_rqd;
	}

	atomic_dec(&pblk->inflight_io);

	if (rqd.error) {
		pblk_log_write_err(pblk, &rqd);
		ret = -EIO;
	}

clear_rqd:
	pblk_free_rqd_meta(pblk, &rqd);
	return ret;
}