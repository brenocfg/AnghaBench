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
struct exynos_mic {scalar_t__ reg; scalar_t__ i80_mode; } ;

/* Variables and functions */
 int MIC_BS_CHG_OUT ; 
 int MIC_CORE_EN ; 
 int MIC_CORE_VER_CONTROL ; 
 int MIC_MODE_SEL_COMMAND_MODE ; 
 int MIC_MODE_SEL_MASK ; 
 int MIC_ON_REG ; 
 scalar_t__ MIC_OP ; 
 int MIC_PSR_EN ; 
 int MIC_UPD_REG ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mic_set_reg_on(struct exynos_mic *mic, bool enable)
{
	u32 reg = readl(mic->reg + MIC_OP);

	if (enable) {
		reg &= ~(MIC_MODE_SEL_MASK | MIC_CORE_VER_CONTROL | MIC_PSR_EN);
		reg |= (MIC_CORE_EN | MIC_BS_CHG_OUT | MIC_ON_REG);

		reg  &= ~MIC_MODE_SEL_COMMAND_MODE;
		if (mic->i80_mode)
			reg |= MIC_MODE_SEL_COMMAND_MODE;
	} else {
		reg &= ~MIC_CORE_EN;
	}

	reg |= MIC_UPD_REG;
	writel(reg, mic->reg + MIC_OP);
}