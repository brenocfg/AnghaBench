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
typedef  scalar_t__ u32 ;
struct i915_request {int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 scalar_t__ i915_request_global_seqno (struct i915_request const*) ; 
 int i915_seqno_passed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool i915_request_started(const struct i915_request *rq)
{
	u32 seqno;

	seqno = i915_request_global_seqno(rq);
	if (!seqno)
		return false;

	return i915_seqno_passed(intel_engine_get_seqno(rq->engine),
				 seqno - 1);
}