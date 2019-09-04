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
typedef  int u32 ;
struct msm_dsi_host {int /*<<< orphan*/  dma_comp; int /*<<< orphan*/  video_comp; int /*<<< orphan*/  id; int /*<<< orphan*/  intr_lock; int /*<<< orphan*/  ctrl_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ) ; 
 int DSI_IRQ_CMD_DMA_DONE ; 
 int DSI_IRQ_ERROR ; 
 int DSI_IRQ_VIDEO_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_DSI_INTR_CTRL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_error (struct msm_dsi_host*) ; 
 int dsi_read (struct msm_dsi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t dsi_host_irq(int irq, void *ptr)
{
	struct msm_dsi_host *msm_host = ptr;
	u32 isr;
	unsigned long flags;

	if (!msm_host->ctrl_base)
		return IRQ_HANDLED;

	spin_lock_irqsave(&msm_host->intr_lock, flags);
	isr = dsi_read(msm_host, REG_DSI_INTR_CTRL);
	dsi_write(msm_host, REG_DSI_INTR_CTRL, isr);
	spin_unlock_irqrestore(&msm_host->intr_lock, flags);

	DBG("isr=0x%x, id=%d", isr, msm_host->id);

	if (isr & DSI_IRQ_ERROR)
		dsi_error(msm_host);

	if (isr & DSI_IRQ_VIDEO_DONE)
		complete(&msm_host->video_comp);

	if (isr & DSI_IRQ_CMD_DMA_DONE)
		complete(&msm_host->dma_comp);

	return IRQ_HANDLED;
}