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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline dma_addr_t
huge_gem_object_dma_size(struct drm_i915_gem_object *obj)
{
	return obj->base.size;
}