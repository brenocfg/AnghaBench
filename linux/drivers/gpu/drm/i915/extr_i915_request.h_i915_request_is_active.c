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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct i915_request {TYPE_1__ fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_FENCE_FLAG_ACTIVE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool i915_request_is_active(const struct i915_request *rq)
{
	return test_bit(I915_FENCE_FLAG_ACTIVE, &rq->fence.flags);
}