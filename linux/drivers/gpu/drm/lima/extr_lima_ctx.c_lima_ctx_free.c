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
typedef  int /*<<< orphan*/  u32 ;
struct lima_ctx_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  handles; } ;
struct lima_ctx {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_ctx_do_release ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct lima_ctx* xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lima_ctx_free(struct lima_ctx_mgr *mgr, u32 id)
{
	struct lima_ctx *ctx;
	int ret = 0;

	mutex_lock(&mgr->lock);
	ctx = xa_erase(&mgr->handles, id);
	if (ctx)
		kref_put(&ctx->refcnt, lima_ctx_do_release);
	else
		ret = -EINVAL;
	mutex_unlock(&mgr->lock);
	return ret;
}