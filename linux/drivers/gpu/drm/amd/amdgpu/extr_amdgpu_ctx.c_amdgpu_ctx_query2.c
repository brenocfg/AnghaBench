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
struct TYPE_2__ {int flags; int hangs; } ;
union drm_amdgpu_ctx_out {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ctx_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctx_handles; } ;
struct amdgpu_fpriv {struct amdgpu_ctx_mgr ctx_mgr; } ;
struct amdgpu_device {int /*<<< orphan*/  vram_lost_counter; int /*<<< orphan*/  gpu_reset_counter; } ;
struct amdgpu_ctx {scalar_t__ reset_counter; scalar_t__ vram_lost_counter; unsigned long ras_counter_ue; unsigned long ras_counter_ce; int /*<<< orphan*/  guilty; } ;

/* Variables and functions */
 int AMDGPU_CTX_QUERY2_FLAGS_GUILTY ; 
 int AMDGPU_CTX_QUERY2_FLAGS_RAS_CE ; 
 int AMDGPU_CTX_QUERY2_FLAGS_RAS_UE ; 
 int AMDGPU_CTX_QUERY2_FLAGS_RESET ; 
 int AMDGPU_CTX_QUERY2_FLAGS_VRAMLOST ; 
 int EINVAL ; 
 unsigned long amdgpu_ras_query_error_count (struct amdgpu_device*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct amdgpu_ctx* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_ctx_query2(struct amdgpu_device *adev,
	struct amdgpu_fpriv *fpriv, uint32_t id,
	union drm_amdgpu_ctx_out *out)
{
	struct amdgpu_ctx *ctx;
	struct amdgpu_ctx_mgr *mgr;
	unsigned long ras_counter;

	if (!fpriv)
		return -EINVAL;

	mgr = &fpriv->ctx_mgr;
	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	if (!ctx) {
		mutex_unlock(&mgr->lock);
		return -EINVAL;
	}

	out->state.flags = 0x0;
	out->state.hangs = 0x0;

	if (ctx->reset_counter != atomic_read(&adev->gpu_reset_counter))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_RESET;

	if (ctx->vram_lost_counter != atomic_read(&adev->vram_lost_counter))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_VRAMLOST;

	if (atomic_read(&ctx->guilty))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_GUILTY;

	/*query ue count*/
	ras_counter = amdgpu_ras_query_error_count(adev, false);
	/*ras counter is monotonic increasing*/
	if (ras_counter != ctx->ras_counter_ue) {
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_RAS_UE;
		ctx->ras_counter_ue = ras_counter;
	}

	/*query ce count*/
	ras_counter = amdgpu_ras_query_error_count(adev, true);
	if (ras_counter != ctx->ras_counter_ce) {
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_RAS_CE;
		ctx->ras_counter_ce = ras_counter;
	}

	mutex_unlock(&mgr->lock);
	return 0;
}