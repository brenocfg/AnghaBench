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
typedef  scalar_t__ u32 ;
struct i915_request {scalar_t__ infix; scalar_t__ postfix; TYPE_1__* ring; } ;
struct TYPE_2__ {scalar_t__ size; void* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_NOOP ; 
 int /*<<< orphan*/  memset32 (void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void skip_request(struct i915_request *rq)
{
	void *vaddr = rq->ring->vaddr;
	u32 head;

	head = rq->infix;
	if (rq->postfix < head) {
		memset32(vaddr + head, MI_NOOP,
			 (rq->ring->size - head) / sizeof(u32));
		head = 0;
	}
	memset32(vaddr + head, MI_NOOP, (rq->postfix - head) / sizeof(u32));
}