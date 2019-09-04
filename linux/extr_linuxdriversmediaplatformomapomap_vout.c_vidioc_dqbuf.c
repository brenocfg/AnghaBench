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
typedef  unsigned long u32 ;
struct videobuf_queue {struct videobuf_buffer** bufs; } ;
struct videobuf_buffer {size_t i; scalar_t__ size; } ;
struct v4l2_buffer {size_t index; } ;
struct omap_vout_device {TYPE_2__* vid_dev; scalar_t__* buf_phy_addr; int /*<<< orphan*/  streaming; struct videobuf_queue vbq; } ;
struct file {int f_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int videobuf_dqbuf (struct videobuf_queue*,struct v4l2_buffer*,int) ; 

__attribute__((used)) static int vidioc_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct omap_vout_device *vout = fh;
	struct videobuf_queue *q = &vout->vbq;

	int ret;
	u32 addr;
	unsigned long size;
	struct videobuf_buffer *vb;

	vb = q->bufs[b->index];

	if (!vout->streaming)
		return -EINVAL;

	if (file->f_flags & O_NONBLOCK)
		/* Call videobuf_dqbuf for non blocking mode */
		ret = videobuf_dqbuf(q, (struct v4l2_buffer *)b, 1);
	else
		/* Call videobuf_dqbuf for  blocking mode */
		ret = videobuf_dqbuf(q, (struct v4l2_buffer *)b, 0);

	addr = (unsigned long) vout->buf_phy_addr[vb->i];
	size = (unsigned long) vb->size;
	dma_unmap_single(vout->vid_dev->v4l2_dev.dev,  addr,
				size, DMA_TO_DEVICE);
	return ret;
}