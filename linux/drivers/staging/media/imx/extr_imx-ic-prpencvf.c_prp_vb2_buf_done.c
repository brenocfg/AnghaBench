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
struct TYPE_7__ {int /*<<< orphan*/  phys; } ;
struct prp_priv {size_t ipu_buf_num; int nfb4eof; struct ipuv3_channel* out_ch; scalar_t__ interweave_swap; struct imx_media_buffer** active_vb2_buf; TYPE_2__ underrun_buf; int /*<<< orphan*/  frame_sequence; struct imx_media_video_dev* vdev; } ;
struct ipuv3_channel {int dummy; } ;
struct TYPE_8__ {scalar_t__ bytesperline; int /*<<< orphan*/  field; } ;
struct TYPE_9__ {TYPE_3__ pix; } ;
struct TYPE_10__ {TYPE_4__ fmt; } ;
struct imx_media_video_dev {TYPE_5__ fmt; } ;
struct TYPE_6__ {struct vb2_buffer vb2_buf; int /*<<< orphan*/  sequence; int /*<<< orphan*/  field; } ;
struct imx_media_buffer {TYPE_1__ vbuf; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 struct imx_media_buffer* imx_media_capture_device_next_buf (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  ipu_cpmem_set_buffer (struct ipuv3_channel*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ipu_idmac_buffer_is_ready (struct ipuv3_channel*,size_t) ; 
 int /*<<< orphan*/  ipu_idmac_clear_buffer (struct ipuv3_channel*,size_t) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prp_vb2_buf_done(struct prp_priv *priv, struct ipuv3_channel *ch)
{
	struct imx_media_video_dev *vdev = priv->vdev;
	struct imx_media_buffer *done, *next;
	struct vb2_buffer *vb;
	dma_addr_t phys;

	done = priv->active_vb2_buf[priv->ipu_buf_num];
	if (done) {
		done->vbuf.field = vdev->fmt.fmt.pix.field;
		done->vbuf.sequence = priv->frame_sequence;
		vb = &done->vbuf.vb2_buf;
		vb->timestamp = ktime_get_ns();
		vb2_buffer_done(vb, priv->nfb4eof ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
	}

	priv->frame_sequence++;
	priv->nfb4eof = false;

	/* get next queued buffer */
	next = imx_media_capture_device_next_buf(vdev);
	if (next) {
		phys = vb2_dma_contig_plane_dma_addr(&next->vbuf.vb2_buf, 0);
		priv->active_vb2_buf[priv->ipu_buf_num] = next;
	} else {
		phys = priv->underrun_buf.phys;
		priv->active_vb2_buf[priv->ipu_buf_num] = NULL;
	}

	if (ipu_idmac_buffer_is_ready(ch, priv->ipu_buf_num))
		ipu_idmac_clear_buffer(ch, priv->ipu_buf_num);

	if (priv->interweave_swap && ch == priv->out_ch)
		phys += vdev->fmt.fmt.pix.bytesperline;

	ipu_cpmem_set_buffer(ch, priv->ipu_buf_num, phys);
}