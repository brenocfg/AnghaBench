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
struct TYPE_2__ {int context; } ;
struct i915_request {TYPE_1__ fence; } ;
struct hang {int /*<<< orphan*/ * seqno; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hws_seqno(const struct hang *h, const struct i915_request *rq)
{
	return READ_ONCE(h->seqno[rq->fence.context % (PAGE_SIZE/sizeof(u32))]);
}