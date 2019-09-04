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
struct dw_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_COMP_PARAM_1 ; 
 int /*<<< orphan*/  dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 

u32 i2c_dw_read_comp_param(struct dw_i2c_dev *dev)
{
	return dw_readl(dev, DW_IC_COMP_PARAM_1);
}