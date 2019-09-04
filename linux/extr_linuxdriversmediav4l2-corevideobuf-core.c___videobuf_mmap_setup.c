#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {TYPE_2__** bufs; TYPE_1__* int_ops; } ;
typedef  enum v4l2_memory { ____Placeholder_v4l2_memory } v4l2_memory ;
struct TYPE_4__ {unsigned int i; int memory; unsigned int bsize; unsigned int boff; } ;
struct TYPE_3__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_QTYPE_OPS ; 
 unsigned int PAGE_ALIGN (unsigned int) ; 
#define  V4L2_MEMORY_DMABUF 131 
#define  V4L2_MEMORY_MMAP 130 
#define  V4L2_MEMORY_OVERLAY 129 
#define  V4L2_MEMORY_USERPTR 128 
 int __videobuf_free (struct videobuf_queue*) ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned int,unsigned int) ; 
 TYPE_2__* videobuf_alloc_vb (struct videobuf_queue*) ; 

int __videobuf_mmap_setup(struct videobuf_queue *q,
			unsigned int bcount, unsigned int bsize,
			enum v4l2_memory memory)
{
	unsigned int i;
	int err;

	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	err = __videobuf_free(q);
	if (0 != err)
		return err;

	/* Allocate and initialize buffers */
	for (i = 0; i < bcount; i++) {
		q->bufs[i] = videobuf_alloc_vb(q);

		if (NULL == q->bufs[i])
			break;

		q->bufs[i]->i      = i;
		q->bufs[i]->memory = memory;
		q->bufs[i]->bsize  = bsize;
		switch (memory) {
		case V4L2_MEMORY_MMAP:
			q->bufs[i]->boff = PAGE_ALIGN(bsize) * i;
			break;
		case V4L2_MEMORY_USERPTR:
		case V4L2_MEMORY_OVERLAY:
		case V4L2_MEMORY_DMABUF:
			/* nothing */
			break;
		}
	}

	if (!i)
		return -ENOMEM;

	dprintk(1, "mmap setup: %d buffers, %d bytes each\n", i, bsize);

	return i;
}