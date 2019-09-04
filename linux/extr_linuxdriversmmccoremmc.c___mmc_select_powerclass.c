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
struct TYPE_2__ {int vdd; int /*<<< orphan*/  clock; } ;
struct mmc_host {TYPE_1__ ios; } ;
struct mmc_ext_csd {unsigned int raw_pwr_cl_26_195; unsigned int raw_pwr_cl_52_195; unsigned int raw_pwr_cl_ddr_52_195; unsigned int raw_pwr_cl_200_195; unsigned int raw_pwr_cl_26_360; unsigned int raw_pwr_cl_52_360; unsigned int raw_pwr_cl_ddr_52_360; unsigned int raw_pwr_cl_ddr_200_360; unsigned int raw_pwr_cl_200_360; int /*<<< orphan*/  generic_cmd6_time; } ;
struct mmc_card {struct mmc_ext_csd ext_csd; struct mmc_host* host; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EXT_CSD_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 unsigned int EXT_CSD_DDR_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  EXT_CSD_POWER_CLASS ; 
 unsigned int EXT_CSD_PWR_CL_4BIT_MASK ; 
 unsigned int EXT_CSD_PWR_CL_4BIT_SHIFT ; 
 unsigned int EXT_CSD_PWR_CL_8BIT_MASK ; 
 unsigned int EXT_CSD_PWR_CL_8BIT_SHIFT ; 
 int /*<<< orphan*/  MMC_HIGH_26_MAX_DTR ; 
 int /*<<< orphan*/  MMC_HIGH_52_MAX_DTR ; 
 int /*<<< orphan*/  MMC_HS200_MAX_DTR ; 
#define  MMC_VDD_165_195 137 
#define  MMC_VDD_27_28 136 
#define  MMC_VDD_28_29 135 
#define  MMC_VDD_29_30 134 
#define  MMC_VDD_30_31 133 
#define  MMC_VDD_31_32 132 
#define  MMC_VDD_32_33 131 
#define  MMC_VDD_33_34 130 
#define  MMC_VDD_34_35 129 
#define  MMC_VDD_35_36 128 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mmc_select_powerclass(struct mmc_card *card,
				   unsigned int bus_width)
{
	struct mmc_host *host = card->host;
	struct mmc_ext_csd *ext_csd = &card->ext_csd;
	unsigned int pwrclass_val = 0;
	int err = 0;

	switch (1 << host->ios.vdd) {
	case MMC_VDD_165_195:
		if (host->ios.clock <= MMC_HIGH_26_MAX_DTR)
			pwrclass_val = ext_csd->raw_pwr_cl_26_195;
		else if (host->ios.clock <= MMC_HIGH_52_MAX_DTR)
			pwrclass_val = (bus_width <= EXT_CSD_BUS_WIDTH_8) ?
				ext_csd->raw_pwr_cl_52_195 :
				ext_csd->raw_pwr_cl_ddr_52_195;
		else if (host->ios.clock <= MMC_HS200_MAX_DTR)
			pwrclass_val = ext_csd->raw_pwr_cl_200_195;
		break;
	case MMC_VDD_27_28:
	case MMC_VDD_28_29:
	case MMC_VDD_29_30:
	case MMC_VDD_30_31:
	case MMC_VDD_31_32:
	case MMC_VDD_32_33:
	case MMC_VDD_33_34:
	case MMC_VDD_34_35:
	case MMC_VDD_35_36:
		if (host->ios.clock <= MMC_HIGH_26_MAX_DTR)
			pwrclass_val = ext_csd->raw_pwr_cl_26_360;
		else if (host->ios.clock <= MMC_HIGH_52_MAX_DTR)
			pwrclass_val = (bus_width <= EXT_CSD_BUS_WIDTH_8) ?
				ext_csd->raw_pwr_cl_52_360 :
				ext_csd->raw_pwr_cl_ddr_52_360;
		else if (host->ios.clock <= MMC_HS200_MAX_DTR)
			pwrclass_val = (bus_width == EXT_CSD_DDR_BUS_WIDTH_8) ?
				ext_csd->raw_pwr_cl_ddr_200_360 :
				ext_csd->raw_pwr_cl_200_360;
		break;
	default:
		pr_warn("%s: Voltage range not supported for power class\n",
			mmc_hostname(host));
		return -EINVAL;
	}

	if (bus_width & (EXT_CSD_BUS_WIDTH_8 | EXT_CSD_DDR_BUS_WIDTH_8))
		pwrclass_val = (pwrclass_val & EXT_CSD_PWR_CL_8BIT_MASK) >>
				EXT_CSD_PWR_CL_8BIT_SHIFT;
	else
		pwrclass_val = (pwrclass_val & EXT_CSD_PWR_CL_4BIT_MASK) >>
				EXT_CSD_PWR_CL_4BIT_SHIFT;

	/* If the power class is different from the default value */
	if (pwrclass_val > 0) {
		err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_POWER_CLASS,
				 pwrclass_val,
				 card->ext_csd.generic_cmd6_time);
	}

	return err;
}