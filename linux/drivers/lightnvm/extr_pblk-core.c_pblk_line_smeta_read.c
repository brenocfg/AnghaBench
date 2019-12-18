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
struct pblk_line_meta {int smeta_sec; } ;
struct pblk_line {int /*<<< orphan*/  smeta; int /*<<< orphan*/  id; } ;
struct pblk {int /*<<< orphan*/  inflight_io; struct pblk_line_meta lm; } ;
struct nvm_rq {int nr_ppas; int is_seq; scalar_t__ error; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NVM_OP_PREAD ; 
 scalar_t__ NVM_RSP_WARN_HIGHECC ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 int pblk_alloc_rqd_meta (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_free_rqd_meta (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_line_smeta_start (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_log_read_err (struct pblk*,struct nvm_rq*) ; 
 int pblk_submit_io_sync (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 

int pblk_line_smeta_read(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct ppa_addr *ppa_list;
	struct nvm_rq rqd;
	u64 paddr = pblk_line_smeta_start(pblk, line);
	int i, ret;

	memset(&rqd, 0, sizeof(struct nvm_rq));

	ret = pblk_alloc_rqd_meta(pblk, &rqd);
	if (ret)
		return ret;

	rqd.opcode = NVM_OP_PREAD;
	rqd.nr_ppas = lm->smeta_sec;
	rqd.is_seq = 1;
	ppa_list = nvm_rq_to_ppa_list(&rqd);

	for (i = 0; i < lm->smeta_sec; i++, paddr++)
		ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);

	ret = pblk_submit_io_sync(pblk, &rqd, line->smeta);
	if (ret) {
		pblk_err(pblk, "smeta I/O submission failed: %d\n", ret);
		goto clear_rqd;
	}

	atomic_dec(&pblk->inflight_io);

	if (rqd.error && rqd.error != NVM_RSP_WARN_HIGHECC) {
		pblk_log_read_err(pblk, &rqd);
		ret = -EIO;
	}

clear_rqd:
	pblk_free_rqd_meta(pblk, &rqd);
	return ret;
}