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
struct igt_spinner {int /*<<< orphan*/ * seqno; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_1__ fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int seqno_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
hws_seqno(const struct igt_spinner *spin, const struct i915_request *rq)
{
	u32 *seqno = spin->seqno + seqno_offset(rq->fence.context);

	return READ_ONCE(*seqno);
}