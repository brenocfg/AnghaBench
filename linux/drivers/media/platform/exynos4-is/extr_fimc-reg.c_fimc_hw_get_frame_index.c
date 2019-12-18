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
struct fimc_dev {scalar_t__ regs; TYPE_1__* drv_data; } ;
typedef  int s32 ;
struct TYPE_2__ {scalar_t__ cistatus2; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CISTATUS ; 
 scalar_t__ FIMC_REG_CISTATUS2 ; 
 int FIMC_REG_CISTATUS_FRAMECNT_MASK ; 
 int FIMC_REG_CISTATUS_FRAMECNT_SHIFT ; 
 int readl (scalar_t__) ; 

s32 fimc_hw_get_frame_index(struct fimc_dev *dev)
{
	s32 reg;

	if (dev->drv_data->cistatus2) {
		reg = readl(dev->regs + FIMC_REG_CISTATUS2) & 0x3f;
		return reg - 1;
	}

	reg = readl(dev->regs + FIMC_REG_CISTATUS);

	return (reg & FIMC_REG_CISTATUS_FRAMECNT_MASK) >>
		FIMC_REG_CISTATUS_FRAMECNT_SHIFT;
}