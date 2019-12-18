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
struct intel_timeline_hwsp {TYPE_1__* gt; TYPE_2__* vma; } ;
struct intel_timeline_cacheline {int /*<<< orphan*/  active; int /*<<< orphan*/  vaddr; struct intel_timeline_hwsp* hwsp; } ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CACHELINE_BITS ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct intel_timeline_cacheline* ERR_CAST (void*) ; 
 struct intel_timeline_cacheline* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  __cacheline_active ; 
 int /*<<< orphan*/  __cacheline_retire ; 
 int /*<<< orphan*/  i915_active_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* i915_gem_object_pin_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_get (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct intel_timeline_cacheline*) ; 
 struct intel_timeline_cacheline* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pack_bits (void*,unsigned int) ; 

__attribute__((used)) static struct intel_timeline_cacheline *
cacheline_alloc(struct intel_timeline_hwsp *hwsp, unsigned int cacheline)
{
	struct intel_timeline_cacheline *cl;
	void *vaddr;

	GEM_BUG_ON(cacheline >= BIT(CACHELINE_BITS));

	cl = kmalloc(sizeof(*cl), GFP_KERNEL);
	if (!cl)
		return ERR_PTR(-ENOMEM);

	vaddr = i915_gem_object_pin_map(hwsp->vma->obj, I915_MAP_WB);
	if (IS_ERR(vaddr)) {
		kfree(cl);
		return ERR_CAST(vaddr);
	}

	i915_vma_get(hwsp->vma);
	cl->hwsp = hwsp;
	cl->vaddr = page_pack_bits(vaddr, cacheline);

	i915_active_init(hwsp->gt->i915, &cl->active,
			 __cacheline_active, __cacheline_retire);

	return cl;
}