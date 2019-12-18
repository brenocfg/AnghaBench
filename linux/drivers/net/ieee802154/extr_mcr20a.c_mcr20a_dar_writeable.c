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
#define  DAR_CLK_OUT_CTRL 158 
#define  DAR_IRQ_STS1 157 
#define  DAR_IRQ_STS2 156 
#define  DAR_IRQ_STS3 155 
#define  DAR_OVERWRITE_VER 154 
#define  DAR_PA_PWR 153 
#define  DAR_PHY_CTRL1 152 
#define  DAR_PHY_CTRL2 151 
#define  DAR_PHY_CTRL3 150 
#define  DAR_PHY_CTRL4 149 
#define  DAR_PLL_FRAC0_LSB 148 
#define  DAR_PLL_FRAC0_MSB 147 
#define  DAR_PLL_INT0 146 
#define  DAR_PWR_MODES 145 
#define  DAR_SRC_ADDRS_SUM_LSB 144 
#define  DAR_SRC_ADDRS_SUM_MSB 143 
#define  DAR_SRC_CTRL 142 
#define  DAR_T1CMP_LSB 141 
#define  DAR_T1CMP_MSB 140 
#define  DAR_T1CMP_USB 139 
#define  DAR_T2CMP_LSB 138 
#define  DAR_T2CMP_MSB 137 
#define  DAR_T2CMP_USB 136 
#define  DAR_T2PRIMECMP_LSB 135 
#define  DAR_T2PRIMECMP_MSB 134 
#define  DAR_T3CMP_LSB 133 
#define  DAR_T3CMP_MSB 132 
#define  DAR_T3CMP_USB 131 
#define  DAR_T4CMP_LSB 130 
#define  DAR_T4CMP_MSB 129 
#define  DAR_T4CMP_USB 128 

__attribute__((used)) static bool
mcr20a_dar_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DAR_IRQ_STS1:
	case DAR_IRQ_STS2:
	case DAR_IRQ_STS3:
	case DAR_PHY_CTRL1:
	case DAR_PHY_CTRL2:
	case DAR_PHY_CTRL3:
	case DAR_PHY_CTRL4:
	case DAR_SRC_CTRL:
	case DAR_SRC_ADDRS_SUM_LSB:
	case DAR_SRC_ADDRS_SUM_MSB:
	case DAR_T3CMP_LSB:
	case DAR_T3CMP_MSB:
	case DAR_T3CMP_USB:
	case DAR_T2PRIMECMP_LSB:
	case DAR_T2PRIMECMP_MSB:
	case DAR_T1CMP_LSB:
	case DAR_T1CMP_MSB:
	case DAR_T1CMP_USB:
	case DAR_T2CMP_LSB:
	case DAR_T2CMP_MSB:
	case DAR_T2CMP_USB:
	case DAR_T4CMP_LSB:
	case DAR_T4CMP_MSB:
	case DAR_T4CMP_USB:
	case DAR_PLL_INT0:
	case DAR_PLL_FRAC0_LSB:
	case DAR_PLL_FRAC0_MSB:
	case DAR_PA_PWR:
	/* no DAR_ACM */
	case DAR_OVERWRITE_VER:
	case DAR_CLK_OUT_CTRL:
	case DAR_PWR_MODES:
		return true;
	default:
		return false;
	}
}