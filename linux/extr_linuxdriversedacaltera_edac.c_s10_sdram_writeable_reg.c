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
struct device {int dummy; } ;

/* Variables and functions */
#define  S10_DIAGINTTEST_OFST 135 
#define  S10_ECCCTRL1_OFST 134 
#define  S10_ERRINTEN_OFST 133 
#define  S10_INTMODE_OFST 132 
#define  S10_INTSTAT_OFST 131 
#define  S10_SYSMGR_ECC_INTMASK_CLR_OFST 130 
#define  S10_SYSMGR_ECC_INTMASK_SET_OFST 129 
#define  S10_SYSMGR_ECC_INTMASK_VAL_OFST 128 

__attribute__((used)) static bool s10_sdram_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case S10_ECCCTRL1_OFST:
	case S10_ERRINTEN_OFST:
	case S10_INTMODE_OFST:
	case S10_INTSTAT_OFST:
	case S10_DIAGINTTEST_OFST:
	case S10_SYSMGR_ECC_INTMASK_VAL_OFST:
	case S10_SYSMGR_ECC_INTMASK_SET_OFST:
	case S10_SYSMGR_ECC_INTMASK_CLR_OFST:
		return true;
	}
	return false;
}