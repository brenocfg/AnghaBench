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
struct videobuf_buffer {int /*<<< orphan*/  state; } ;
struct viu_buf {struct videobuf_buffer vb; } ;
struct videobuf_queue {TYPE_1__* int_ops; } ;
struct TYPE_2__ {void* (* vaddr ) (struct videobuf_buffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  in_interrupt () ; 
 void* stub1 (struct videobuf_buffer*) ; 
 int /*<<< orphan*/  videobuf_dma_contig_free (struct videobuf_queue*,struct videobuf_buffer*) ; 
 int /*<<< orphan*/  videobuf_waiton (struct videobuf_queue*,struct videobuf_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_buffer(struct videobuf_queue *vq, struct viu_buf *buf)
{
	struct videobuf_buffer *vb = &buf->vb;
	void *vaddr = NULL;

	BUG_ON(in_interrupt());

	videobuf_waiton(vq, &buf->vb, 0, 0);

	if (vq->int_ops && vq->int_ops->vaddr)
		vaddr = vq->int_ops->vaddr(vb);

	if (vaddr)
		videobuf_dma_contig_free(vq, &buf->vb);

	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}