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
struct vb2_queue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct sun4i_csi {TYPE_2__ scratch; int /*<<< orphan*/  dev; TYPE_1__ vdev; int /*<<< orphan*/  qlock; int /*<<< orphan*/  src_subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_all_buffers (struct sun4i_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun4i_csi_capture_stop (struct sun4i_csi*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sun4i_csi* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void sun4i_csi_stop_streaming(struct vb2_queue *vq)
{
	struct sun4i_csi *csi = vb2_get_drv_priv(vq);
	unsigned long flags;

	dev_dbg(csi->dev, "Stopping capture\n");

	v4l2_subdev_call(csi->src_subdev, video, s_stream, 0);
	sun4i_csi_capture_stop(csi);

	/* Release all active buffers */
	spin_lock_irqsave(&csi->qlock, flags);
	return_all_buffers(csi, VB2_BUF_STATE_ERROR);
	spin_unlock_irqrestore(&csi->qlock, flags);

	media_pipeline_stop(&csi->vdev.entity);

	dma_free_coherent(csi->dev, csi->scratch.size, csi->scratch.vaddr,
			  csi->scratch.paddr);
}