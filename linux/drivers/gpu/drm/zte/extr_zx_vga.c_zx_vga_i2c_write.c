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
struct zx_vga {scalar_t__ mmio; } ;
struct i2c_msg {int len; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ DDC_ADDR ; 
 int EINVAL ; 
 scalar_t__ VGA_DEVICE_ADDR ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int zx_vga_i2c_write(struct zx_vga *vga, struct i2c_msg *msg)
{
	/*
	 * The DDC I2C adapter is only for reading EDID data, so we assume
	 * that the write to this adapter must be the EDID data offset.
	 */
	if ((msg->len != 1) || ((msg->addr != DDC_ADDR)))
		return -EINVAL;

	/* Hardware will take care of the slave address shifting */
	zx_writel(vga->mmio + VGA_DEVICE_ADDR, msg->addr);

	return 0;
}