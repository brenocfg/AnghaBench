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
struct sha256_hash_ctx {int dummy; } ;
struct sha256_ctx_mgr {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 struct sha256_hash_ctx* sha256_ctx_mgr_resubmit (struct sha256_ctx_mgr*,struct sha256_hash_ctx*) ; 
 scalar_t__ sha256_job_mgr_get_comp_job (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sha256_hash_ctx
		*sha256_ctx_mgr_get_comp_ctx(struct sha256_ctx_mgr *mgr)
{
	/*
	 * If get_comp_job returns NULL, there are no jobs complete.
	 * If get_comp_job returns a job, verify that it is safe to return to
	 * the user. If it is not ready, resubmit the job to finish processing.
	 * If sha256_ctx_mgr_resubmit returned a job, it is ready to be
	 * returned. Otherwise, all jobs currently being managed by the
	 * hash_ctx_mgr still need processing.
	 */
	struct sha256_hash_ctx *ctx;

	ctx = (struct sha256_hash_ctx *) sha256_job_mgr_get_comp_job(&mgr->mgr);
	return sha256_ctx_mgr_resubmit(mgr, ctx);
}