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
struct vsp1_video {TYPE_1__* rwpf; } ;
struct TYPE_6__ {scalar_t__* addr; } ;
struct vsp1_vb2_buffer {TYPE_3__ mem; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {unsigned int num_planes; int /*<<< orphan*/  vb2_queue; } ;
struct v4l2_pix_format_mplane {unsigned int num_planes; TYPE_2__* plane_fmt; } ;
struct TYPE_5__ {scalar_t__ sizeimage; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane format; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vsp1_vb2_buffer* to_vsp1_vb2_buffer (struct vb2_v4l2_buffer*) ; 
 scalar_t__ vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,unsigned int) ; 
 struct vsp1_video* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,unsigned int) ; 

__attribute__((used)) static int vsp1_video_buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vsp1_video *video = vb2_get_drv_priv(vb->vb2_queue);
	struct vsp1_vb2_buffer *buf = to_vsp1_vb2_buffer(vbuf);
	const struct v4l2_pix_format_mplane *format = &video->rwpf->format;
	unsigned int i;

	if (vb->num_planes < format->num_planes)
		return -EINVAL;

	for (i = 0; i < vb->num_planes; ++i) {
		buf->mem.addr[i] = vb2_dma_contig_plane_dma_addr(vb, i);

		if (vb2_plane_size(vb, i) < format->plane_fmt[i].sizeimage)
			return -EINVAL;
	}

	for ( ; i < 3; ++i)
		buf->mem.addr[i] = 0;

	return 0;
}