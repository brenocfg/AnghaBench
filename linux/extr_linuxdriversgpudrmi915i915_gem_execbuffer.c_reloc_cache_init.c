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
struct TYPE_3__ {int allocated; } ;
struct reloc_cache {int page; int gen; int has_fence; scalar_t__ rq_size; int /*<<< orphan*/ * rq; TYPE_1__ node; int /*<<< orphan*/  needs_unfenced; int /*<<< orphan*/  use_64bit_reloc; int /*<<< orphan*/  has_llc; scalar_t__ vaddr; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  unfenced_needs_alignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_64BIT_RELOC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_LLC (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 

__attribute__((used)) static void reloc_cache_init(struct reloc_cache *cache,
			     struct drm_i915_private *i915)
{
	cache->page = -1;
	cache->vaddr = 0;
	/* Must be a variable in the struct to allow GCC to unroll. */
	cache->gen = INTEL_GEN(i915);
	cache->has_llc = HAS_LLC(i915);
	cache->use_64bit_reloc = HAS_64BIT_RELOC(i915);
	cache->has_fence = cache->gen < 4;
	cache->needs_unfenced = INTEL_INFO(i915)->unfenced_needs_alignment;
	cache->node.allocated = false;
	cache->rq = NULL;
	cache->rq_size = 0;
}