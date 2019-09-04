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
struct i915_perf_stream {scalar_t__ ctx; int /*<<< orphan*/  link; TYPE_1__* ops; scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct i915_perf_stream*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_context_put (scalar_t__) ; 
 int /*<<< orphan*/  i915_perf_disable_locked (struct i915_perf_stream*) ; 
 int /*<<< orphan*/  kfree (struct i915_perf_stream*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct i915_perf_stream*) ; 

__attribute__((used)) static void i915_perf_destroy_locked(struct i915_perf_stream *stream)
{
	if (stream->enabled)
		i915_perf_disable_locked(stream);

	if (stream->ops->destroy)
		stream->ops->destroy(stream);

	list_del(&stream->link);

	if (stream->ctx)
		i915_gem_context_put(stream->ctx);

	kfree(stream);
}