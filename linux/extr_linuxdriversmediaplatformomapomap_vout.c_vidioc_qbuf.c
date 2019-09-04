#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {TYPE_1__** bufs; } ;
struct TYPE_8__ {scalar_t__ userptr; } ;
struct v4l2_buffer {scalar_t__ type; size_t index; scalar_t__ memory; scalar_t__ length; TYPE_3__ m; } ;
struct TYPE_9__ {scalar_t__ req_status; } ;
struct TYPE_7__ {scalar_t__ sizeimage; } ;
struct omap_vout_device {size_t buffer_allocated; TYPE_5__* vid_dev; TYPE_4__ vrfb_dma_tx; TYPE_2__ pix; struct videobuf_queue vbq; } ;
struct file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_6__ {scalar_t__ memory; } ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_NOT_ALLOTED ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 scalar_t__ is_rotation_enabled (struct omap_vout_device*) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 
 int videobuf_qbuf (struct videobuf_queue*,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_qbuf(struct file *file, void *fh,
			struct v4l2_buffer *buffer)
{
	struct omap_vout_device *vout = fh;
	struct videobuf_queue *q = &vout->vbq;

	if ((V4L2_BUF_TYPE_VIDEO_OUTPUT != buffer->type) ||
			(buffer->index >= vout->buffer_allocated) ||
			(q->bufs[buffer->index]->memory != buffer->memory)) {
		return -EINVAL;
	}
	if (V4L2_MEMORY_USERPTR == buffer->memory) {
		if ((buffer->length < vout->pix.sizeimage) ||
				(0 == buffer->m.userptr)) {
			return -EINVAL;
		}
	}

	if ((is_rotation_enabled(vout)) &&
			vout->vrfb_dma_tx.req_status == DMA_CHAN_NOT_ALLOTED) {
		v4l2_warn(&vout->vid_dev->v4l2_dev,
				"DMA Channel not allocated for Rotation\n");
		return -EINVAL;
	}

	return videobuf_qbuf(q, buffer);
}