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
struct TYPE_2__ {scalar_t__ seqno; } ;
struct i915_request {TYPE_1__ fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsp_seqno (struct i915_request const*) ; 
 int i915_seqno_passed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool __i915_request_has_started(const struct i915_request *rq)
{
	return i915_seqno_passed(hwsp_seqno(rq), rq->fence.seqno - 1);
}