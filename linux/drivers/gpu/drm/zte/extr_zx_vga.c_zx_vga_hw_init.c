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
struct zx_vga {scalar_t__ mmio; int /*<<< orphan*/  i2c_wclk; } ;

/* Variables and functions */
 int DDC_ADDR ; 
 int DIV_ROUND_UP (unsigned long,int) ; 
 scalar_t__ VGA_AUTO_DETECT_PARA ; 
 scalar_t__ VGA_AUTO_DETECT_SEL ; 
 scalar_t__ VGA_CLK_DIV_FS ; 
 scalar_t__ VGA_CMD_CFG ; 
 int /*<<< orphan*/  VGA_CMD_TRANS ; 
 int VGA_DETECT_SEL_NO_DEVICE ; 
 scalar_t__ VGA_DEVICE_ADDR ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_vga_hw_init(struct zx_vga *vga)
{
	unsigned long ref = clk_get_rate(vga->i2c_wclk);
	int div;

	/*
	 * Set up I2C fast speed divider per formula below to get 400kHz.
	 *   scl = ref / ((div + 1) * 4)
	 */
	div = DIV_ROUND_UP(ref / 1000, 400 * 4) - 1;
	zx_writel(vga->mmio + VGA_CLK_DIV_FS, div);

	/* Set up device detection */
	zx_writel(vga->mmio + VGA_AUTO_DETECT_PARA, 0x80);
	zx_writel(vga->mmio + VGA_AUTO_DETECT_SEL, VGA_DETECT_SEL_NO_DEVICE);

	/*
	 * We need to poke monitor via DDC bus to get connection irq
	 * start working.
	 */
	zx_writel(vga->mmio + VGA_DEVICE_ADDR, DDC_ADDR);
	zx_writel_mask(vga->mmio + VGA_CMD_CFG, VGA_CMD_TRANS, VGA_CMD_TRANS);
}