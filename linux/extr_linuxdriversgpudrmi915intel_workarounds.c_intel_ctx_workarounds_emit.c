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
typedef  int /*<<< orphan*/  u32 ;
struct i915_workarounds {int count; TYPE_2__* reg; } ;
struct i915_request {TYPE_3__* engine; TYPE_1__* i915; } ;
struct TYPE_6__ {int (* emit_flush ) (struct i915_request*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {struct i915_workarounds workarounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_BARRIER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct i915_request*,int /*<<< orphan*/ ) ; 

int intel_ctx_workarounds_emit(struct i915_request *rq)
{
	struct i915_workarounds *w = &rq->i915->workarounds;
	u32 *cs;
	int ret, i;

	if (w->count == 0)
		return 0;

	ret = rq->engine->emit_flush(rq, EMIT_BARRIER);
	if (ret)
		return ret;

	cs = intel_ring_begin(rq, (w->count * 2 + 2));
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(w->count);
	for (i = 0; i < w->count; i++) {
		*cs++ = w->reg[i].addr;
		*cs++ = w->reg[i].value;
	}
	*cs++ = MI_NOOP;

	intel_ring_advance(rq, cs);

	ret = rq->engine->emit_flush(rq, EMIT_BARRIER);
	if (ret)
		return ret;

	return 0;
}