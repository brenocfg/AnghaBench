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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  sizeimage; } ;
struct TYPE_9__ {TYPE_3__ pix; } ;
struct TYPE_10__ {TYPE_4__ fmt; } ;
struct isp_video_fh {TYPE_5__ format; struct isp_video* video; } ;
struct isp_video {TYPE_1__* isp; int /*<<< orphan*/  error; } ;
struct TYPE_7__ {int /*<<< orphan*/  vb2_buf; } ;
struct isp_buffer {int /*<<< orphan*/  dma; TYPE_2__ vb; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct isp_buffer* to_isp_buffer (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct isp_video_fh* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp_video_buffer_prepare(struct vb2_buffer *buf)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(buf);
	struct isp_video_fh *vfh = vb2_get_drv_priv(buf->vb2_queue);
	struct isp_buffer *buffer = to_isp_buffer(vbuf);
	struct isp_video *video = vfh->video;
	dma_addr_t addr;

	/* Refuse to prepare the buffer is the video node has registered an
	 * error. We don't need to take any lock here as the operation is
	 * inherently racy. The authoritative check will be performed in the
	 * queue handler, which can't return an error, this check is just a best
	 * effort to notify userspace as early as possible.
	 */
	if (unlikely(video->error))
		return -EIO;

	addr = vb2_dma_contig_plane_dma_addr(buf, 0);
	if (!IS_ALIGNED(addr, 32)) {
		dev_dbg(video->isp->dev,
			"Buffer address must be aligned to 32 bytes boundary.\n");
		return -EINVAL;
	}

	vb2_set_plane_payload(&buffer->vb.vb2_buf, 0,
			      vfh->format.fmt.pix.sizeimage);
	buffer->dma = addr;

	return 0;
}