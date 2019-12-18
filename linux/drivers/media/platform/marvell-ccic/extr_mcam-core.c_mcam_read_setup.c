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
struct mcam_camera {scalar_t__ buffer_mode; scalar_t__ nbufs; scalar_t__ bus_type; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ B_vmalloc ; 
 int /*<<< orphan*/  CF_DMA_ACTIVE ; 
 int /*<<< orphan*/  CF_SG_RESTART ; 
 int ENOMEM ; 
 int /*<<< orphan*/  S_STREAMING ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mcam_alloc_dma_bufs (struct mcam_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_cam_configure (struct mcam_camera*) ; 
 int mcam_ctlr_configure (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_ctlr_irq_enable (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_ctlr_start (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_disable_mipi (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_enable_mipi (struct mcam_camera*) ; 
 scalar_t__ mcam_needs_config (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_reset_buffers (struct mcam_camera*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcam_read_setup(struct mcam_camera *cam)
{
	int ret;
	unsigned long flags;

	/*
	 * Configuration.  If we still don't have DMA buffers,
	 * make one last, desperate attempt.
	 */
	if (cam->buffer_mode == B_vmalloc && cam->nbufs == 0 &&
			mcam_alloc_dma_bufs(cam, 0))
		return -ENOMEM;

	if (mcam_needs_config(cam)) {
		mcam_cam_configure(cam);
		ret = mcam_ctlr_configure(cam);
		if (ret)
			return ret;
	}

	/*
	 * Turn it loose.
	 */
	spin_lock_irqsave(&cam->dev_lock, flags);
	clear_bit(CF_DMA_ACTIVE, &cam->flags);
	mcam_reset_buffers(cam);
	if (cam->bus_type == V4L2_MBUS_CSI2_DPHY)
		mcam_enable_mipi(cam);
	else
		mcam_disable_mipi(cam);
	mcam_ctlr_irq_enable(cam);
	cam->state = S_STREAMING;
	if (!test_bit(CF_SG_RESTART, &cam->flags))
		mcam_ctlr_start(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	return 0;
}