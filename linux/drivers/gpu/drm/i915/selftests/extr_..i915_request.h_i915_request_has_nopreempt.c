#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_request {int flags; } ;

/* Variables and functions */
 int I915_REQUEST_NOPREEMPT ; 
 int unlikely (int) ; 

__attribute__((used)) static inline bool i915_request_has_nopreempt(const struct i915_request *rq)
{
	/* Preemption should only be disabled very rarely */
	return unlikely(rq->flags & I915_REQUEST_NOPREEMPT);
}