#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  vma; } ;
struct i915_perf_stream {TYPE_2__ oa_buffer; struct drm_i915_private* dev_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_VMA_RELEASE_MAP ; 
 int /*<<< orphan*/  i915_vma_unpin_and_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_oa_buffer(struct i915_perf_stream *stream)
{
	struct drm_i915_private *i915 = stream->dev_priv;

	mutex_lock(&i915->drm.struct_mutex);

	i915_vma_unpin_and_release(&stream->oa_buffer.vma,
				   I915_VMA_RELEASE_MAP);

	mutex_unlock(&i915->drm.struct_mutex);

	stream->oa_buffer.vaddr = NULL;
}