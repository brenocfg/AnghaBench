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
struct videobuf_queue {size_t msize; int /*<<< orphan*/ * int_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_ops ; 
 void* videobuf_alloc_vb (struct videobuf_queue*) ; 

void *videobuf_sg_alloc(size_t size)
{
	struct videobuf_queue q;

	/* Required to make generic handler to call __videobuf_alloc */
	q.int_ops = &sg_ops;

	q.msize = size;

	return videobuf_alloc_vb(&q);
}