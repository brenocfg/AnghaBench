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
struct fb_info {int /*<<< orphan*/  device; struct atmel_lcdfb_info* par; } ;
struct atmel_lcdfb_info {int /*<<< orphan*/  task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_LCDC_ICR ; 
 int /*<<< orphan*/  ATMEL_LCDC_ISR ; 
 int ATMEL_LCDC_UFLWI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int lcdc_readl (struct atmel_lcdfb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_writel (struct atmel_lcdfb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t atmel_lcdfb_interrupt(int irq, void *dev_id)
{
	struct fb_info *info = dev_id;
	struct atmel_lcdfb_info *sinfo = info->par;
	u32 status;

	status = lcdc_readl(sinfo, ATMEL_LCDC_ISR);
	if (status & ATMEL_LCDC_UFLWI) {
		dev_warn(info->device, "FIFO underflow %#x\n", status);
		/* reset DMA and FIFO to avoid screen shifting */
		schedule_work(&sinfo->task);
	}
	lcdc_writel(sinfo, ATMEL_LCDC_ICR, status);
	return IRQ_HANDLED;
}