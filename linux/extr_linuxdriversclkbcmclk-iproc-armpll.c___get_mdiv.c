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
struct iproc_arm_pll {scalar_t__ base; } ;

/* Variables and functions */
#define  ARM_PLL_FID_CH0_SLOW_CLK 131 
#define  ARM_PLL_FID_CH1_FAST_CLK 130 
#define  ARM_PLL_FID_CRYSTAL_CLK 129 
#define  ARM_PLL_FID_SYS_CLK 128 
 int EFAULT ; 
 int IPROC_CLK_PLLARMCTL5_H_MDIV_MASK ; 
 scalar_t__ IPROC_CLK_PLLARMCTL5_OFFSET ; 
 int IPROC_CLK_PLLARMC_MDIV_MASK ; 
 scalar_t__ IPROC_CLK_PLLARMC_OFFSET ; 
 unsigned int __get_fid (struct iproc_arm_pll*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int __get_mdiv(struct iproc_arm_pll *pll)
{
	unsigned int fid;
	int mdiv;
	u32 val;

	fid = __get_fid(pll);

	switch (fid) {
	case ARM_PLL_FID_CRYSTAL_CLK:
	case ARM_PLL_FID_SYS_CLK:
		mdiv = 1;
		break;

	case ARM_PLL_FID_CH0_SLOW_CLK:
		val = readl(pll->base + IPROC_CLK_PLLARMC_OFFSET);
		mdiv = val & IPROC_CLK_PLLARMC_MDIV_MASK;
		if (mdiv == 0)
			mdiv = 256;
		break;

	case ARM_PLL_FID_CH1_FAST_CLK:
		val = readl(pll->base +	IPROC_CLK_PLLARMCTL5_OFFSET);
		mdiv = val & IPROC_CLK_PLLARMCTL5_H_MDIV_MASK;
		if (mdiv == 0)
			mdiv = 256;
		break;

	default:
		mdiv = -EFAULT;
	}

	return mdiv;
}