#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i915_request {int head; int tail; TYPE_3__* ring; TYPE_2__* batch; int /*<<< orphan*/  postfix; } ;
struct drm_printer {int dummy; } ;
struct TYPE_6__ {unsigned int size; void* vaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  hexdump (struct drm_printer*,void*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_request_ring(struct drm_printer *m, struct i915_request *rq)
{
	void *ring;
	int size;

	drm_printf(m,
		   "[head %04x, postfix %04x, tail %04x, batch 0x%08x_%08x]:\n",
		   rq->head, rq->postfix, rq->tail,
		   rq->batch ? upper_32_bits(rq->batch->node.start) : ~0u,
		   rq->batch ? lower_32_bits(rq->batch->node.start) : ~0u);

	size = rq->tail - rq->head;
	if (rq->tail < rq->head)
		size += rq->ring->size;

	ring = kmalloc(size, GFP_ATOMIC);
	if (ring) {
		const void *vaddr = rq->ring->vaddr;
		unsigned int head = rq->head;
		unsigned int len = 0;

		if (rq->tail < head) {
			len = rq->ring->size - head;
			memcpy(ring, vaddr + head, len);
			head = 0;
		}
		memcpy(ring + len, vaddr + head, size - len);

		hexdump(m, ring, size);
		kfree(ring);
	}
}