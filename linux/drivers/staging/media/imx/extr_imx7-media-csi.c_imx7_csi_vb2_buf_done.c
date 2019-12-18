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
struct vb2_buffer {int /*<<< orphan*/  timestamp; } ;
struct TYPE_6__ {int /*<<< orphan*/  field; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct imx_media_video_dev {TYPE_3__ fmt; } ;
struct TYPE_9__ {struct vb2_buffer vb2_buf; int /*<<< orphan*/  sequence; int /*<<< orphan*/  field; } ;
struct imx_media_buffer {TYPE_4__ vbuf; } ;
struct TYPE_10__ {int /*<<< orphan*/  phys; } ;
struct imx7_csi {size_t buf_num; struct imx_media_buffer** active_vb2_buf; TYPE_5__ underrun_buf; int /*<<< orphan*/  frame_sequence; struct imx_media_video_dev* vdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  imx7_csi_update_buf (struct imx7_csi*,int /*<<< orphan*/ ,size_t) ; 
 struct imx_media_buffer* imx_media_capture_device_next_buf (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7_csi_vb2_buf_done(struct imx7_csi *csi)
{
	struct imx_media_video_dev *vdev = csi->vdev;
	struct imx_media_buffer *done, *next;
	struct vb2_buffer *vb;
	dma_addr_t phys;

	done = csi->active_vb2_buf[csi->buf_num];
	if (done) {
		done->vbuf.field = vdev->fmt.fmt.pix.field;
		done->vbuf.sequence = csi->frame_sequence;
		vb = &done->vbuf.vb2_buf;
		vb->timestamp = ktime_get_ns();
		vb2_buffer_done(vb, VB2_BUF_STATE_DONE);
	}
	csi->frame_sequence++;

	/* get next queued buffer */
	next = imx_media_capture_device_next_buf(vdev);
	if (next) {
		phys = vb2_dma_contig_plane_dma_addr(&next->vbuf.vb2_buf, 0);
		csi->active_vb2_buf[csi->buf_num] = next;
	} else {
		phys = csi->underrun_buf.phys;
		csi->active_vb2_buf[csi->buf_num] = NULL;
	}

	imx7_csi_update_buf(csi, phys, csi->buf_num);
}