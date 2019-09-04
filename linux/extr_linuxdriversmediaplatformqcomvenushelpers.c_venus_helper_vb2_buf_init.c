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
struct venus_inst {int /*<<< orphan*/  registeredbufs; } ;
struct venus_buffer {int /*<<< orphan*/  reg_list; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {scalar_t__ type; int /*<<< orphan*/  vb2_queue; } ;
struct sg_table {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct venus_buffer* to_venus_buffer (struct vb2_v4l2_buffer*) ; 
 struct sg_table* vb2_dma_sg_plane_desc (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct venus_inst* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

int venus_helper_vb2_buf_init(struct vb2_buffer *vb)
{
	struct venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct venus_buffer *buf = to_venus_buffer(vbuf);
	struct sg_table *sgt;

	sgt = vb2_dma_sg_plane_desc(vb, 0);
	if (!sgt)
		return -EFAULT;

	buf->size = vb2_plane_size(vb, 0);
	buf->dma_addr = sg_dma_address(sgt->sgl);

	if (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		list_add_tail(&buf->reg_list, &inst->registeredbufs);

	return 0;
}