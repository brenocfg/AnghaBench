#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {int /*<<< orphan*/  obj; int /*<<< orphan*/  i915; } ;
typedef  struct i915_vma u32 ;
struct intel_context {TYPE_3__* engine; } ;
struct i915_wa_list {unsigned int count; int /*<<< orphan*/  name; struct i915_wa* list; } ;
struct i915_wa {int /*<<< orphan*/  reg; } ;
struct i915_request {int /*<<< orphan*/  obj; int /*<<< orphan*/  i915; } ;
struct TYPE_6__ {TYPE_2__* gt; } ;
struct TYPE_5__ {TYPE_1__* ggtt; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIME ; 
 int HZ ; 
 int /*<<< orphan*/  I915_MAP_WB ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* create_scratch (int /*<<< orphan*/ *,unsigned int) ; 
 struct i915_vma* i915_gem_object_pin_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_add (struct i915_vma*) ; 
 scalar_t__ i915_request_wait (struct i915_vma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_vma_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 struct i915_vma* intel_context_create_request (struct intel_context*) ; 
 scalar_t__ mcr_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wa_list_srm (struct i915_vma*,struct i915_wa_list const* const,struct i915_vma*) ; 
 int /*<<< orphan*/  wa_verify (struct i915_wa const*,struct i915_vma,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int engine_wa_list_verify(struct intel_context *ce,
				 const struct i915_wa_list * const wal,
				 const char *from)
{
	const struct i915_wa *wa;
	struct i915_request *rq;
	struct i915_vma *vma;
	unsigned int i;
	u32 *results;
	int err;

	if (!wal->count)
		return 0;

	vma = create_scratch(&ce->engine->gt->ggtt->vm, wal->count);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	rq = intel_context_create_request(ce);
	if (IS_ERR(rq)) {
		err = PTR_ERR(rq);
		goto err_vma;
	}

	err = wa_list_srm(rq, wal, vma);
	if (err)
		goto err_vma;

	i915_request_add(rq);
	if (i915_request_wait(rq, 0, HZ / 5) < 0) {
		err = -ETIME;
		goto err_vma;
	}

	results = i915_gem_object_pin_map(vma->obj, I915_MAP_WB);
	if (IS_ERR(results)) {
		err = PTR_ERR(results);
		goto err_vma;
	}

	err = 0;
	for (i = 0, wa = wal->list; i < wal->count; i++, wa++) {
		if (mcr_range(rq->i915, i915_mmio_reg_offset(wa->reg)))
			continue;

		if (!wa_verify(wa, results[i], wal->name, from))
			err = -ENXIO;
	}

	i915_gem_object_unpin_map(vma->obj);

err_vma:
	i915_vma_unpin(vma);
	i915_vma_put(vma);
	return err;
}