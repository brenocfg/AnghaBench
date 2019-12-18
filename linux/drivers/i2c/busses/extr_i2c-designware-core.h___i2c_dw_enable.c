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
 int /*<<< orphan*/  DW_IC_ENABLE ; 
 int /*<<< orphan*/  dw_writel (struct dw_i2c_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __i2c_dw_enable(struct dw_i2c_dev *dev)
{
	dw_writel(dev, 1, DW_IC_ENABLE);
}