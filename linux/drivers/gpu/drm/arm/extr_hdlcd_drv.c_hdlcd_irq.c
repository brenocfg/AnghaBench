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
struct hdlcd_drm_private {int /*<<< orphan*/  crtc; int /*<<< orphan*/  vsync_count; int /*<<< orphan*/  bus_error_count; int /*<<< orphan*/  dma_end_count; int /*<<< orphan*/  buffer_underrun_count; } ;
struct drm_device {struct hdlcd_drm_private* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long HDLCD_INTERRUPT_BUS_ERROR ; 
 unsigned long HDLCD_INTERRUPT_DMA_END ; 
 unsigned long HDLCD_INTERRUPT_UNDERRUN ; 
 unsigned long HDLCD_INTERRUPT_VSYNC ; 
 int /*<<< orphan*/  HDLCD_REG_INT_CLEAR ; 
 int /*<<< orphan*/  HDLCD_REG_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 unsigned long hdlcd_read (struct hdlcd_drm_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t hdlcd_irq(int irq, void *arg)
{
	struct drm_device *drm = arg;
	struct hdlcd_drm_private *hdlcd = drm->dev_private;
	unsigned long irq_status;

	irq_status = hdlcd_read(hdlcd, HDLCD_REG_INT_STATUS);

#ifdef CONFIG_DEBUG_FS
	if (irq_status & HDLCD_INTERRUPT_UNDERRUN)
		atomic_inc(&hdlcd->buffer_underrun_count);

	if (irq_status & HDLCD_INTERRUPT_DMA_END)
		atomic_inc(&hdlcd->dma_end_count);

	if (irq_status & HDLCD_INTERRUPT_BUS_ERROR)
		atomic_inc(&hdlcd->bus_error_count);

	if (irq_status & HDLCD_INTERRUPT_VSYNC)
		atomic_inc(&hdlcd->vsync_count);

#endif
	if (irq_status & HDLCD_INTERRUPT_VSYNC)
		drm_crtc_handle_vblank(&hdlcd->crtc);

	/* acknowledge interrupt(s) */
	hdlcd_write(hdlcd, HDLCD_REG_INT_CLEAR, irq_status);

	return IRQ_HANDLED;
}