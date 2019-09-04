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
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {TYPE_1__* i915; } ;
struct i915_gpu_error {int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/  stalled_mask; } ;
struct TYPE_2__ {struct i915_gpu_error gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_RESET_HANDOFF ; 
 int /*<<< orphan*/  i915_reset_count (struct i915_gpu_error*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 fake_hangcheck(struct i915_request *rq, u32 mask)
{
	struct i915_gpu_error *error = &rq->i915->gpu_error;
	u32 reset_count = i915_reset_count(error);

	error->stalled_mask = mask;

	/* set_bit() must be after we have setup the backchannel (mask) */
	smp_mb__before_atomic();
	set_bit(I915_RESET_HANDOFF, &error->flags);

	wake_up_all(&error->wait_queue);

	return reset_count;
}