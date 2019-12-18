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
struct tegra_dpaux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAUX_HYBRID_PADCTL ; 
 int DPAUX_HYBRID_PADCTL_AUX_CMH (int) ; 
 int DPAUX_HYBRID_PADCTL_AUX_DRVI (int) ; 
 int DPAUX_HYBRID_PADCTL_AUX_DRVZ (int) ; 
 int DPAUX_HYBRID_PADCTL_AUX_INPUT_RCV ; 
 int DPAUX_HYBRID_PADCTL_I2C_SCL_INPUT_RCV ; 
 int DPAUX_HYBRID_PADCTL_I2C_SDA_INPUT_RCV ; 
 int DPAUX_HYBRID_PADCTL_MODE_AUX ; 
 int DPAUX_HYBRID_PADCTL_MODE_I2C ; 
#define  DPAUX_PADCTL_FUNC_AUX 130 
#define  DPAUX_PADCTL_FUNC_I2C 129 
#define  DPAUX_PADCTL_FUNC_OFF 128 
 int ENOTSUPP ; 
 int /*<<< orphan*/  tegra_dpaux_pad_power_down (struct tegra_dpaux*) ; 
 int /*<<< orphan*/  tegra_dpaux_pad_power_up (struct tegra_dpaux*) ; 
 int /*<<< orphan*/  tegra_dpaux_writel (struct tegra_dpaux*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dpaux_pad_config(struct tegra_dpaux *dpaux, unsigned function)
{
	u32 value;

	switch (function) {
	case DPAUX_PADCTL_FUNC_AUX:
		value = DPAUX_HYBRID_PADCTL_AUX_CMH(2) |
			DPAUX_HYBRID_PADCTL_AUX_DRVZ(4) |
			DPAUX_HYBRID_PADCTL_AUX_DRVI(0x18) |
			DPAUX_HYBRID_PADCTL_AUX_INPUT_RCV |
			DPAUX_HYBRID_PADCTL_MODE_AUX;
		break;

	case DPAUX_PADCTL_FUNC_I2C:
		value = DPAUX_HYBRID_PADCTL_I2C_SDA_INPUT_RCV |
			DPAUX_HYBRID_PADCTL_I2C_SCL_INPUT_RCV |
			DPAUX_HYBRID_PADCTL_AUX_CMH(2) |
			DPAUX_HYBRID_PADCTL_AUX_DRVZ(4) |
			DPAUX_HYBRID_PADCTL_AUX_DRVI(0x18) |
			DPAUX_HYBRID_PADCTL_MODE_I2C;
		break;

	case DPAUX_PADCTL_FUNC_OFF:
		tegra_dpaux_pad_power_down(dpaux);
		return 0;

	default:
		return -ENOTSUPP;
	}

	tegra_dpaux_writel(dpaux, value, DPAUX_HYBRID_PADCTL);
	tegra_dpaux_pad_power_up(dpaux);

	return 0;
}