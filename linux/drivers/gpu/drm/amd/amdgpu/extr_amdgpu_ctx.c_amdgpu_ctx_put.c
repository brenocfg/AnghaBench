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
struct amdgpu_ctx {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_ctx_do_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int amdgpu_ctx_put(struct amdgpu_ctx *ctx)
{
	if (ctx == NULL)
		return -EINVAL;

	kref_put(&ctx->refcount, amdgpu_ctx_do_release);
	return 0;
}