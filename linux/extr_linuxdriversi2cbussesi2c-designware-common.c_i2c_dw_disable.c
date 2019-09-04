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
struct dw_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_CLR_INTR ; 
 int /*<<< orphan*/  DW_IC_INTR_MASK ; 
 int /*<<< orphan*/  __i2c_dw_disable (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_writel (struct dw_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i2c_dw_disable(struct dw_i2c_dev *dev)
{
	/* Disable controller */
	__i2c_dw_disable(dev);

	/* Disable all interupts */
	dw_writel(dev, 0, DW_IC_INTR_MASK);
	dw_readl(dev, DW_IC_CLR_INTR);
}