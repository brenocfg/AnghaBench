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
struct msm_kms {unsigned int pending_crtc_mask; TYPE_1__* funcs; int /*<<< orphan*/  commit_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_commit ) (struct msm_kms*) ;int /*<<< orphan*/  (* complete_commit ) (struct msm_kms*,unsigned int) ;int /*<<< orphan*/  (* wait_flush ) (struct msm_kms*,unsigned int) ;int /*<<< orphan*/  (* flush_commit ) (struct msm_kms*,unsigned int) ;int /*<<< orphan*/  (* enable_commit ) (struct msm_kms*) ;} ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*) ; 
 int /*<<< orphan*/  stub2 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub4 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub5 (struct msm_kms*) ; 
 int /*<<< orphan*/  trace_msm_atomic_async_commit_finish (unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_async_commit_start (unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_flush_commit (unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_wait_flush_finish (unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_wait_flush_start (unsigned int) ; 

__attribute__((used)) static void msm_atomic_async_commit(struct msm_kms *kms, int crtc_idx)
{
	unsigned crtc_mask = BIT(crtc_idx);

	trace_msm_atomic_async_commit_start(crtc_mask);

	mutex_lock(&kms->commit_lock);

	if (!(kms->pending_crtc_mask & crtc_mask)) {
		mutex_unlock(&kms->commit_lock);
		goto out;
	}

	kms->pending_crtc_mask &= ~crtc_mask;

	kms->funcs->enable_commit(kms);

	/*
	 * Flush hardware updates:
	 */
	trace_msm_atomic_flush_commit(crtc_mask);
	kms->funcs->flush_commit(kms, crtc_mask);
	mutex_unlock(&kms->commit_lock);

	/*
	 * Wait for flush to complete:
	 */
	trace_msm_atomic_wait_flush_start(crtc_mask);
	kms->funcs->wait_flush(kms, crtc_mask);
	trace_msm_atomic_wait_flush_finish(crtc_mask);

	mutex_lock(&kms->commit_lock);
	kms->funcs->complete_commit(kms, crtc_mask);
	mutex_unlock(&kms->commit_lock);
	kms->funcs->disable_commit(kms);

out:
	trace_msm_atomic_async_commit_finish(crtc_mask);
}