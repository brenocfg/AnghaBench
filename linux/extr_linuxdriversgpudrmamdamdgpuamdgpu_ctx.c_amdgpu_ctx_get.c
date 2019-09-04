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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ctx_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctx_handles; } ;
struct amdgpu_fpriv {struct amdgpu_ctx_mgr ctx_mgr; } ;
struct amdgpu_ctx {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 struct amdgpu_ctx* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct amdgpu_ctx *amdgpu_ctx_get(struct amdgpu_fpriv *fpriv, uint32_t id)
{
	struct amdgpu_ctx *ctx;
	struct amdgpu_ctx_mgr *mgr;

	if (!fpriv)
		return NULL;

	mgr = &fpriv->ctx_mgr;

	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	if (ctx)
		kref_get(&ctx->refcount);
	mutex_unlock(&mgr->lock);
	return ctx;
}