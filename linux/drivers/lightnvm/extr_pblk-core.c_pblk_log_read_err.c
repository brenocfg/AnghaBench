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
struct pblk {int /*<<< orphan*/  read_failed; int /*<<< orphan*/  read_high_ecc; int /*<<< orphan*/  read_empty; } ;
struct nvm_rq {int error; } ;

/* Variables and functions */
 int NVM_RSP_ERR_EMPTYPAGE ; 
#define  NVM_RSP_ERR_FAILCRC 130 
#define  NVM_RSP_ERR_FAILECC 129 
#define  NVM_RSP_WARN_HIGHECC 128 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_print_failed_rqd (struct pblk*,struct nvm_rq*,int) ; 

void pblk_log_read_err(struct pblk *pblk, struct nvm_rq *rqd)
{
	/* Empty page read is not necessarily an error (e.g., L2P recovery) */
	if (rqd->error == NVM_RSP_ERR_EMPTYPAGE) {
		atomic_long_inc(&pblk->read_empty);
		return;
	}

	switch (rqd->error) {
	case NVM_RSP_WARN_HIGHECC:
		atomic_long_inc(&pblk->read_high_ecc);
		break;
	case NVM_RSP_ERR_FAILECC:
	case NVM_RSP_ERR_FAILCRC:
		atomic_long_inc(&pblk->read_failed);
		break;
	default:
		pblk_err(pblk, "unknown read error:%d\n", rqd->error);
	}
#ifdef CONFIG_NVM_PBLK_DEBUG
	pblk_print_failed_rqd(pblk, rqd, rqd->error);
#endif
}