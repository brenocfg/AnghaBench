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
struct zx_vga {int connected; int /*<<< orphan*/  complete; scalar_t__ mmio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ VGA_AUTO_DETECT_SEL ; 
 int /*<<< orphan*/  VGA_CLEAR_IRQ ; 
 int /*<<< orphan*/  VGA_DETECT_SEL_NO_DEVICE ; 
 int VGA_DEVICE_CONNECTED ; 
 int VGA_DEVICE_DISCONNECTED ; 
 scalar_t__ VGA_I2C_STATUS ; 
 int VGA_TRANS_DONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int zx_readl (scalar_t__) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t zx_vga_irq_handler(int irq, void *dev_id)
{
	struct zx_vga *vga = dev_id;
	u32 status;

	status = zx_readl(vga->mmio + VGA_I2C_STATUS);

	/* Clear interrupt status */
	zx_writel_mask(vga->mmio + VGA_I2C_STATUS, VGA_CLEAR_IRQ,
		       VGA_CLEAR_IRQ);

	if (status & VGA_DEVICE_CONNECTED) {
		/*
		 * Since VGA_DETECT_SEL bits need to be reset for switching DDC
		 * bus from device detection to EDID read, rather than setting
		 * up HAS_DEVICE bit here, we need to do that in .get_modes
		 * hook for unplug detecting after EDID read succeeds.
		 */
		vga->connected = true;
		return IRQ_WAKE_THREAD;
	}

	if (status & VGA_DEVICE_DISCONNECTED) {
		zx_writel(vga->mmio + VGA_AUTO_DETECT_SEL,
			  VGA_DETECT_SEL_NO_DEVICE);
		vga->connected = false;
		return IRQ_WAKE_THREAD;
	}

	if (status & VGA_TRANS_DONE) {
		complete(&vga->complete);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}