#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i915_gem_context {int flags; TYPE_1__* ppgtt; } ;
struct i915_execbuffer {int /*<<< orphan*/  context_flags; TYPE_3__* i915; int /*<<< orphan*/ * vm; struct i915_gem_context* ctx; TYPE_5__* args; TYPE_4__* file; } ;
struct TYPE_10__ {int /*<<< orphan*/  rsvd1; } ;
struct TYPE_9__ {int /*<<< orphan*/  driver_priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  vm; } ;
struct TYPE_8__ {TYPE_2__ ggtt; } ;
struct TYPE_6__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int CONTEXT_NO_ZEROMAP ; 
 int ENOENT ; 
 int /*<<< orphan*/  __EXEC_OBJECT_NEEDS_BIAS ; 
 struct i915_gem_context* i915_gem_context_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int eb_select_context(struct i915_execbuffer *eb)
{
	struct i915_gem_context *ctx;

	ctx = i915_gem_context_lookup(eb->file->driver_priv, eb->args->rsvd1);
	if (unlikely(!ctx))
		return -ENOENT;

	eb->ctx = ctx;
	eb->vm = ctx->ppgtt ? &ctx->ppgtt->vm : &eb->i915->ggtt.vm;

	eb->context_flags = 0;
	if (ctx->flags & CONTEXT_NO_ZEROMAP)
		eb->context_flags |= __EXEC_OBJECT_NEEDS_BIAS;

	return 0;
}