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
struct TYPE_2__ {void (* lcdc_callback ) (void*) ;int bus_pick_width; int /*<<< orphan*/  lock; int /*<<< orphan*/  vsync_dma_pending; scalar_t__ tearsync_mode; int /*<<< orphan*/  tearsync_line; int /*<<< orphan*/  bus_pick_count; int /*<<< orphan*/  fck; void* lcdc_callback_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOSSI_INIT1_REG ; 
 int /*<<< orphan*/  WR_ACCESS ; 
 int /*<<< orphan*/  _set_bits_per_cycle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _set_tearsync_mode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_enable_lcd_dma () ; 
 int /*<<< orphan*/  set_cycles (int) ; 
 int /*<<< orphan*/  set_timing (int /*<<< orphan*/ ) ; 
 TYPE_1__ sossi ; 
 int /*<<< orphan*/  sossi_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sossi_start_transfer () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sossi_transfer_area(int width, int height,
				void (callback)(void *data), void *data)
{
	BUG_ON(callback == NULL);

	sossi.lcdc_callback = callback;
	sossi.lcdc_callback_data = data;

	clk_enable(sossi.fck);
	set_timing(WR_ACCESS);
	_set_bits_per_cycle(sossi.bus_pick_count, sossi.bus_pick_width);
	_set_tearsync_mode(sossi.tearsync_mode, sossi.tearsync_line);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_REG, 1 << 18);
	set_cycles(width * height * sossi.bus_pick_width / 8);

	sossi_start_transfer();
	if (sossi.tearsync_mode) {
		/*
		 * Wait for the sync signal and start the transfer only
		 * then. We can't seem to be able to use HW sync DMA for
		 * this since LCD DMA shows huge latencies, as if it
		 * would ignore some of the DMA requests from SoSSI.
		 */
		unsigned long flags;

		spin_lock_irqsave(&sossi.lock, flags);
		sossi.vsync_dma_pending++;
		spin_unlock_irqrestore(&sossi.lock, flags);
	} else
		/* Just start the transfer right away. */
		omap_enable_lcd_dma();
}