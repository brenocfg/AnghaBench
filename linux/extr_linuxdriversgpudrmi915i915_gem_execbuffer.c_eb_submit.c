#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i915_execbuffer {int /*<<< orphan*/  batch_flags; int /*<<< orphan*/  batch_len; scalar_t__ batch_start_offset; TYPE_2__* batch; int /*<<< orphan*/  request; TYPE_4__* engine; TYPE_3__* args; } ;
struct TYPE_8__ {int (* emit_bb_start ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {scalar_t__ start; } ;
struct TYPE_6__ {TYPE_1__ node; } ;

/* Variables and functions */
 int I915_EXEC_GEN7_SOL_RESET ; 
 int eb_move_to_gpu (struct i915_execbuffer*) ; 
 int i915_reset_gen7_sol_offsets (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eb_submit(struct i915_execbuffer *eb)
{
	int err;

	err = eb_move_to_gpu(eb);
	if (err)
		return err;

	if (eb->args->flags & I915_EXEC_GEN7_SOL_RESET) {
		err = i915_reset_gen7_sol_offsets(eb->request);
		if (err)
			return err;
	}

	err = eb->engine->emit_bb_start(eb->request,
					eb->batch->node.start +
					eb->batch_start_offset,
					eb->batch_len,
					eb->batch_flags);
	if (err)
		return err;

	return 0;
}