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
struct pblk_c_ctx {int dummy; } ;
struct pblk {int /*<<< orphan*/  inflight_io; } ;
struct nvm_rq {TYPE_1__* bio; scalar_t__ error; struct pblk* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct pblk_c_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_check_chunk_state_update (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_complete_write (struct pblk*,struct nvm_rq*,struct pblk_c_ctx*) ; 
 int /*<<< orphan*/  pblk_end_w_fail (struct pblk*,struct nvm_rq*) ; 
 scalar_t__ trace_pblk_chunk_state_enabled () ; 

__attribute__((used)) static void pblk_end_io_write(struct nvm_rq *rqd)
{
	struct pblk *pblk = rqd->private;
	struct pblk_c_ctx *c_ctx = nvm_rq_to_pdu(rqd);

	if (rqd->error) {
		pblk_end_w_fail(pblk, rqd);
		return;
	} else {
		if (trace_pblk_chunk_state_enabled())
			pblk_check_chunk_state_update(pblk, rqd);
#ifdef CONFIG_NVM_PBLK_DEBUG
		WARN_ONCE(rqd->bio->bi_status, "pblk: corrupted write error\n");
#endif
	}

	pblk_complete_write(pblk, rqd, c_ctx);
	atomic_dec(&pblk->inflight_io);
}