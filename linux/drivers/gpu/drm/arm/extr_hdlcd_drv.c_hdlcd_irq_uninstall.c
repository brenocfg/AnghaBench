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
struct hdlcd_drm_private {int dummy; } ;
struct drm_device {struct hdlcd_drm_private* dev_private; } ;

/* Variables and functions */
 unsigned long HDLCD_DEBUG_INT_MASK ; 
 unsigned long HDLCD_INTERRUPT_VSYNC ; 
 int /*<<< orphan*/  HDLCD_REG_INT_MASK ; 
 unsigned long hdlcd_read (struct hdlcd_drm_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void hdlcd_irq_uninstall(struct drm_device *drm)
{
	struct hdlcd_drm_private *hdlcd = drm->dev_private;
	/* disable all the interrupts that we might have enabled */
	unsigned long irq_mask = hdlcd_read(hdlcd, HDLCD_REG_INT_MASK);

#ifdef CONFIG_DEBUG_FS
	/* disable debug interrupts */
	irq_mask &= ~HDLCD_DEBUG_INT_MASK;
#endif

	/* disable vsync interrupts */
	irq_mask &= ~HDLCD_INTERRUPT_VSYNC;

	hdlcd_write(hdlcd, HDLCD_REG_INT_MASK, irq_mask);
}