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
struct sha512_hash_ctx {int dummy; } ;
struct sha512_ctx_mgr {int /*<<< orphan*/  mgr; } ;
struct mcryptd_alg_cstate {int /*<<< orphan*/  work_lock; struct sha512_ctx_mgr* mgr; } ;

/* Variables and functions */
 struct sha512_hash_ctx* sha512_ctx_mgr_resubmit (struct sha512_ctx_mgr*,struct sha512_hash_ctx*) ; 
 scalar_t__ sha512_job_mgr_get_comp_job (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct sha512_hash_ctx
		*sha512_ctx_mgr_get_comp_ctx(struct mcryptd_alg_cstate *cstate)
{
	/*
	 * If get_comp_job returns NULL, there are no jobs complete.
	 * If get_comp_job returns a job, verify that it is safe to return to
	 * the user.
	 * If it is not ready, resubmit the job to finish processing.
	 * If sha512_ctx_mgr_resubmit returned a job, it is ready to be
	 * returned.
	 * Otherwise, all jobs currently being managed by the hash_ctx_mgr
	 * still need processing.
	 */
	struct sha512_ctx_mgr *mgr;
	struct sha512_hash_ctx *ctx;
	unsigned long flags;

	mgr = cstate->mgr;
	spin_lock_irqsave(&cstate->work_lock, flags);
	ctx = (struct sha512_hash_ctx *)
				sha512_job_mgr_get_comp_job(&mgr->mgr);
	ctx = sha512_ctx_mgr_resubmit(mgr, ctx);
	spin_unlock_irqrestore(&cstate->work_lock, flags);
	return ctx;
}