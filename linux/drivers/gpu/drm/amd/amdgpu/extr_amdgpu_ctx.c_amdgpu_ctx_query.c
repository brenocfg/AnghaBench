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
struct TYPE_2__ {int flags; int hangs; int /*<<< orphan*/  reset_status; } ;
union drm_amdgpu_ctx_out {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ctx_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctx_handles; } ;
struct amdgpu_fpriv {struct amdgpu_ctx_mgr ctx_mgr; } ;
struct amdgpu_device {int /*<<< orphan*/  gpu_reset_counter; } ;
struct amdgpu_ctx {unsigned int reset_counter_query; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CTX_NO_RESET ; 
 int /*<<< orphan*/  AMDGPU_CTX_UNKNOWN_RESET ; 
 int EINVAL ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 struct amdgpu_ctx* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_ctx_query(struct amdgpu_device *adev,
			    struct amdgpu_fpriv *fpriv, uint32_t id,
			    union drm_amdgpu_ctx_out *out)
{
	struct amdgpu_ctx *ctx;
	struct amdgpu_ctx_mgr *mgr;
	unsigned reset_counter;

	if (!fpriv)
		return -EINVAL;

	mgr = &fpriv->ctx_mgr;
	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	if (!ctx) {
		mutex_unlock(&mgr->lock);
		return -EINVAL;
	}

	/* TODO: these two are always zero */
	out->state.flags = 0x0;
	out->state.hangs = 0x0;

	/* determine if a GPU reset has occured since the last call */
	reset_counter = atomic_read(&adev->gpu_reset_counter);
	/* TODO: this should ideally return NO, GUILTY, or INNOCENT. */
	if (ctx->reset_counter_query == reset_counter)
		out->state.reset_status = AMDGPU_CTX_NO_RESET;
	else
		out->state.reset_status = AMDGPU_CTX_UNKNOWN_RESET;
	ctx->reset_counter_query = reset_counter;

	mutex_unlock(&mgr->lock);
	return 0;
}