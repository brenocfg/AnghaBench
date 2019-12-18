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
typedef  int /*<<< orphan*/  u32 ;
struct stu300_dev {scalar_t__ virtbase; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ I2C_CR ; 
 int I2C_CR_PERIPHERAL_ENABLE ; 
 scalar_t__ I2C_OAR1 ; 
 scalar_t__ I2C_SR1 ; 
 scalar_t__ I2C_SR2 ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stu300_r8 (scalar_t__) ; 
 int stu300_set_clk (struct stu300_dev*,unsigned long) ; 
 int /*<<< orphan*/  stu300_wr8 (int,scalar_t__) ; 

__attribute__((used)) static int stu300_init_hw(struct stu300_dev *dev)
{
	u32 dummy;
	unsigned long clkrate;
	int ret;

	/* Disable controller */
	stu300_wr8(0x00, dev->virtbase + I2C_CR);
	/*
	 * Set own address to some default value (0x00).
	 * We do not support slave mode anyway.
	 */
	stu300_wr8(0x00, dev->virtbase + I2C_OAR1);
	/*
	 * The I2C controller only operates properly in 26 MHz but we
	 * program this driver as if we didn't know. This will also set the two
	 * high bits of the own address to zero as well.
	 * There is no known hardware issue with running in 13 MHz
	 * However, speeds over 200 kHz are not used.
	 */
	clkrate = clk_get_rate(dev->clk);
	ret = stu300_set_clk(dev, clkrate);

	if (ret)
		return ret;
	/*
	 * Enable block, do it TWICE (hardware glitch)
	 * Setting bit 7 can enable DDC mode. (Not used currently.)
	 */
	stu300_wr8(I2C_CR_PERIPHERAL_ENABLE,
				  dev->virtbase + I2C_CR);
	stu300_wr8(I2C_CR_PERIPHERAL_ENABLE,
				  dev->virtbase + I2C_CR);
	/* Make a dummy read of the status register SR1 & SR2 */
	dummy = stu300_r8(dev->virtbase + I2C_SR2);
	dummy = stu300_r8(dev->virtbase + I2C_SR1);

	return 0;
}