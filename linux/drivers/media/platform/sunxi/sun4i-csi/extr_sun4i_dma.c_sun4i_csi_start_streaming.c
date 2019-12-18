#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct v4l2_fwnode_bus_parallel {int flags; } ;
struct sun4i_csi_format {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct TYPE_8__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; scalar_t__ size; } ;
struct TYPE_7__ {int /*<<< orphan*/  entity; int /*<<< orphan*/  pipe; } ;
struct TYPE_6__ {unsigned int num_planes; int width; TYPE_1__* plane_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  pixelformat; } ;
struct sun4i_csi {int /*<<< orphan*/  qlock; TYPE_4__ scratch; int /*<<< orphan*/  dev; TYPE_3__ vdev; int /*<<< orphan*/  src_subdev; scalar_t__ regs; TYPE_2__ fmt; scalar_t__ sequence; struct v4l2_fwnode_bus_parallel bus; } ;
struct TYPE_5__ {int bytesperline; scalar_t__ sizeimage; } ;

/* Variables and functions */
 int CSI_BUF_CTRL_DBE ; 
 scalar_t__ CSI_BUF_CTRL_REG ; 
 scalar_t__ CSI_BUF_LEN_REG ; 
 int CSI_CFG_HSYNC_POL (unsigned long) ; 
 int CSI_CFG_INPUT_FMT (int /*<<< orphan*/ ) ; 
 int CSI_CFG_OUTPUT_FMT (int /*<<< orphan*/ ) ; 
 int CSI_CFG_PCLK_POL (unsigned long) ; 
 scalar_t__ CSI_CFG_REG ; 
 int CSI_CFG_VSYNC_POL (unsigned long) ; 
 scalar_t__ CSI_INT_EN_REG ; 
 int CSI_INT_FRM_DONE ; 
 int CSI_WIN_CTRL_H_ACTIVE (int /*<<< orphan*/ ) ; 
 scalar_t__ CSI_WIN_CTRL_H_REG ; 
 int CSI_WIN_CTRL_W_ACTIVE (int) ; 
 scalar_t__ CSI_WIN_CTRL_W_REG ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int V4L2_MBUS_DATA_ACTIVE_HIGH ; 
 int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int media_pipeline_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_all_buffers (struct sun4i_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sun4i_csi_buffer_fill_all (struct sun4i_csi*) ; 
 int /*<<< orphan*/  sun4i_csi_capture_start (struct sun4i_csi*) ; 
 int /*<<< orphan*/  sun4i_csi_capture_stop (struct sun4i_csi*) ; 
 struct sun4i_csi_format* sun4i_csi_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sun4i_csi* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun4i_csi_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct sun4i_csi *csi = vb2_get_drv_priv(vq);
	struct v4l2_fwnode_bus_parallel *bus = &csi->bus;
	const struct sun4i_csi_format *csi_fmt;
	unsigned long hsync_pol, pclk_pol, vsync_pol;
	unsigned long flags;
	unsigned int i;
	int ret;

	csi_fmt = sun4i_csi_find_format(&csi->fmt.pixelformat, NULL);
	if (!csi_fmt)
		return -EINVAL;

	dev_dbg(csi->dev, "Starting capture\n");

	csi->sequence = 0;

	/*
	 * We need a scratch buffer in case where we'll not have any
	 * more buffer queued so that we don't error out. One of those
	 * cases is when you end up at the last frame to capture, you
	 * don't havea any buffer queued any more, and yet it doesn't
	 * really matter since you'll never reach the next buffer.
	 *
	 * Since we support the multi-planar API, we need to have a
	 * buffer for each plane. Allocating a single one large enough
	 * to hold all the buffers is simpler, so let's go for that.
	 */
	csi->scratch.size = 0;
	for (i = 0; i < csi->fmt.num_planes; i++)
		csi->scratch.size += csi->fmt.plane_fmt[i].sizeimage;

	csi->scratch.vaddr = dma_alloc_coherent(csi->dev,
						csi->scratch.size,
						&csi->scratch.paddr,
						GFP_KERNEL);
	if (!csi->scratch.vaddr) {
		dev_err(csi->dev, "Failed to allocate scratch buffer\n");
		ret = -ENOMEM;
		goto err_clear_dma_queue;
	}

	ret = media_pipeline_start(&csi->vdev.entity, &csi->vdev.pipe);
	if (ret < 0)
		goto err_free_scratch_buffer;

	spin_lock_irqsave(&csi->qlock, flags);

	/* Setup timings */
	writel(CSI_WIN_CTRL_W_ACTIVE(csi->fmt.width * 2),
	       csi->regs + CSI_WIN_CTRL_W_REG);
	writel(CSI_WIN_CTRL_H_ACTIVE(csi->fmt.height),
	       csi->regs + CSI_WIN_CTRL_H_REG);

	hsync_pol = !!(bus->flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH);
	pclk_pol = !!(bus->flags & V4L2_MBUS_DATA_ACTIVE_HIGH);
	vsync_pol = !!(bus->flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH);
	writel(CSI_CFG_INPUT_FMT(csi_fmt->input) |
	       CSI_CFG_OUTPUT_FMT(csi_fmt->output) |
	       CSI_CFG_VSYNC_POL(vsync_pol) |
	       CSI_CFG_HSYNC_POL(hsync_pol) |
	       CSI_CFG_PCLK_POL(pclk_pol),
	       csi->regs + CSI_CFG_REG);

	/* Setup buffer length */
	writel(csi->fmt.plane_fmt[0].bytesperline,
	       csi->regs + CSI_BUF_LEN_REG);

	/* Prepare our buffers in hardware */
	ret = sun4i_csi_buffer_fill_all(csi);
	if (ret) {
		spin_unlock_irqrestore(&csi->qlock, flags);
		goto err_disable_pipeline;
	}

	/* Enable double buffering */
	writel(CSI_BUF_CTRL_DBE, csi->regs + CSI_BUF_CTRL_REG);

	/* Clear the pending interrupts */
	writel(CSI_INT_FRM_DONE, csi->regs + 0x34);

	/* Enable frame done interrupt */
	writel(CSI_INT_FRM_DONE, csi->regs + CSI_INT_EN_REG);

	sun4i_csi_capture_start(csi);

	spin_unlock_irqrestore(&csi->qlock, flags);

	ret = v4l2_subdev_call(csi->src_subdev, video, s_stream, 1);
	if (ret < 0 && ret != -ENOIOCTLCMD)
		goto err_disable_device;

	return 0;

err_disable_device:
	sun4i_csi_capture_stop(csi);

err_disable_pipeline:
	media_pipeline_stop(&csi->vdev.entity);

err_free_scratch_buffer:
	dma_free_coherent(csi->dev, csi->scratch.size, csi->scratch.vaddr,
			  csi->scratch.paddr);

err_clear_dma_queue:
	spin_lock_irqsave(&csi->qlock, flags);
	return_all_buffers(csi, VB2_BUF_STATE_QUEUED);
	spin_unlock_irqrestore(&csi->qlock, flags);

	return ret;
}