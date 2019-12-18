#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  palette_load_complete; int /*<<< orphan*/  last_frame_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  OMAP_LCDC_CONTROL ; 
 int OMAP_LCDC_IRQ_DONE ; 
 int /*<<< orphan*/  OMAP_LCDC_STATUS ; 
 int OMAP_LCDC_STAT_ABC ; 
 int OMAP_LCDC_STAT_DONE ; 
 int OMAP_LCDC_STAT_FUF ; 
 int OMAP_LCDC_STAT_LINE_INT ; 
 int OMAP_LCDC_STAT_LOADED_PALETTE ; 
 int OMAP_LCDC_STAT_SYNC_LOST ; 
 int OMAP_LCDC_STAT_VSYNC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_controller_async () ; 
 TYPE_1__ lcdc ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_controller (int) ; 

__attribute__((used)) static irqreturn_t lcdc_irq_handler(int irq, void *dev_id)
{
	u32 status;

	status = omap_readl(OMAP_LCDC_STATUS);

	if (status & (OMAP_LCDC_STAT_FUF | OMAP_LCDC_STAT_SYNC_LOST))
		reset_controller(status);
	else {
		if (status & OMAP_LCDC_STAT_DONE) {
			u32 l;

			/*
			 * Disable IRQ_DONE. The status bit will be cleared
			 * only when the controller is reenabled and we don't
			 * want to get more interrupts.
			 */
			l = omap_readl(OMAP_LCDC_CONTROL);
			l &= ~OMAP_LCDC_IRQ_DONE;
			omap_writel(l, OMAP_LCDC_CONTROL);
			complete(&lcdc.last_frame_complete);
		}
		if (status & OMAP_LCDC_STAT_LOADED_PALETTE) {
			disable_controller_async();
			complete(&lcdc.palette_load_complete);
		}
	}

	/*
	 * Clear these interrupt status bits.
	 * Sync_lost, FUF bits were cleared by disabling the LCD controller
	 * LOADED_PALETTE can be cleared this way only in palette only
	 * load mode. In other load modes it's cleared by disabling the
	 * controller.
	 */
	status &= ~(OMAP_LCDC_STAT_VSYNC |
		    OMAP_LCDC_STAT_LOADED_PALETTE |
		    OMAP_LCDC_STAT_ABC |
		    OMAP_LCDC_STAT_LINE_INT);
	omap_writel(status, OMAP_LCDC_STATUS);
	return IRQ_HANDLED;
}