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
struct nmk_i2c_dev {scalar_t__ virtbase; } ;

/* Variables and functions */
 int I2C_CLEAR_ALL_INTS ; 
 scalar_t__ I2C_IMSCR ; 
 int IRQ_MASK (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int disable_interrupts(struct nmk_i2c_dev *dev, u32 irq)
{
	irq = IRQ_MASK(irq);
	writel(readl(dev->virtbase + I2C_IMSCR) & ~(I2C_CLEAR_ALL_INTS & irq),
			dev->virtbase + I2C_IMSCR);
	return 0;
}