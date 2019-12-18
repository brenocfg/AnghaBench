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
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;
struct i915_request {TYPE_1__ fence; int /*<<< orphan*/ * hwsp_seqno; } ;

/* Variables and functions */

__attribute__((used)) static inline void i915_request_mark_complete(struct i915_request *rq)
{
	rq->hwsp_seqno = (u32 *)&rq->fence.seqno; /* decouple from HWSP */
}