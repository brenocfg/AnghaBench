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
struct s5p_cec_dev {int /*<<< orphan*/  reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int CEC_DIV_RATIO ; 
 int /*<<< orphan*/  EXYNOS_HDMI_PHY_CONTROL ; 
 scalar_t__ S5P_CEC_DIVISOR_0 ; 
 scalar_t__ S5P_CEC_DIVISOR_1 ; 
 scalar_t__ S5P_CEC_DIVISOR_2 ; 
 scalar_t__ S5P_CEC_DIVISOR_3 ; 
 int S5P_HDMI_FIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

void s5p_cec_set_divider(struct s5p_cec_dev *cec)
{
	u32 div_ratio, div_val;
	unsigned int reg;

	div_ratio  = S5P_HDMI_FIN / CEC_DIV_RATIO - 1;

	if (regmap_read(cec->pmu, EXYNOS_HDMI_PHY_CONTROL, &reg)) {
		dev_err(cec->dev, "failed to read phy control\n");
		return;
	}

	reg = (reg & ~(0x3FF << 16)) | (div_ratio << 16);

	if (regmap_write(cec->pmu, EXYNOS_HDMI_PHY_CONTROL, reg)) {
		dev_err(cec->dev, "failed to write phy control\n");
		return;
	}

	div_val = CEC_DIV_RATIO * 0.00005 - 1;

	writeb(0x0, cec->reg + S5P_CEC_DIVISOR_3);
	writeb(0x0, cec->reg + S5P_CEC_DIVISOR_2);
	writeb(0x0, cec->reg + S5P_CEC_DIVISOR_1);
	writeb(div_val, cec->reg + S5P_CEC_DIVISOR_0);
}