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
struct intel_wait {int dummy; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_request_global_seqno (struct i915_request const*) ; 
 int intel_wait_update_seqno (struct intel_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
intel_wait_update_request(struct intel_wait *wait,
			  const struct i915_request *rq)
{
	return intel_wait_update_seqno(wait, i915_request_global_seqno(rq));
}