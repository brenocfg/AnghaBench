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
struct pblk {int /*<<< orphan*/  inflight_io; struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {int dummy; } ;
struct nvm_rq {scalar_t__ opcode; } ;

/* Variables and functions */
 int NVM_IO_ERR ; 
 scalar_t__ NVM_OP_PWRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int nvm_submit_io_sync (struct nvm_tgt_dev*,struct nvm_rq*,void*) ; 
 int /*<<< orphan*/  pblk_check_chunk_state_update (struct pblk*,struct nvm_rq*) ; 
 scalar_t__ pblk_check_io (struct pblk*,struct nvm_rq*) ; 
 scalar_t__ trace_pblk_chunk_state_enabled () ; 

int pblk_submit_io_sync(struct pblk *pblk, struct nvm_rq *rqd, void *buf)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	int ret;

	atomic_inc(&pblk->inflight_io);

#ifdef CONFIG_NVM_PBLK_DEBUG
	if (pblk_check_io(pblk, rqd))
		return NVM_IO_ERR;
#endif

	ret = nvm_submit_io_sync(dev, rqd, buf);

	if (trace_pblk_chunk_state_enabled() && !ret &&
	    rqd->opcode == NVM_OP_PWRITE)
		pblk_check_chunk_state_update(pblk, rqd);

	return ret;
}