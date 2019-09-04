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
typedef  unsigned int u32 ;
struct k3_priv {int ctrl_id; } ;
struct dw_mci {struct k3_priv* priv; } ;
struct TYPE_2__ {unsigned int drv_phase; unsigned int smpl_dly; int smpl_phase_max; int smpl_phase_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_SHIFT ; 
 int ENABLE_SHIFT_MAX_SMPL ; 
 int ENABLE_SHIFT_MIN_SMPL ; 
 unsigned int FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int GENCLK_DIV ; 
 int /*<<< orphan*/  GPIO ; 
 int /*<<< orphan*/  GPIO_CLK_DIV_MASK ; 
 unsigned int GPIO_CLK_ENABLE ; 
 int /*<<< orphan*/  GPIO_USE_SAMPLE_DLY_MASK ; 
#define  MMC_TIMING_UHS_SDR104 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  UHS_REG_EXT ; 
 int /*<<< orphan*/  UHS_REG_EXT_SAMPLE_DLY_MASK ; 
 int /*<<< orphan*/  UHS_REG_EXT_SAMPLE_DRVPHASE_MASK ; 
 int /*<<< orphan*/  UHS_REG_EXT_SAMPLE_PHASE_MASK ; 
 int USE_DLY_MAX_SMPL ; 
 int USE_DLY_MIN_SMPL ; 
 TYPE_1__** hs_timing_cfg ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void dw_mci_hs_set_timing(struct dw_mci *host, int timing,
				     int smpl_phase)
{
	u32 drv_phase;
	u32 smpl_dly;
	u32 use_smpl_dly = 0;
	u32 enable_shift = 0;
	u32 reg_value;
	int ctrl_id;
	struct k3_priv *priv;

	priv = host->priv;
	ctrl_id = priv->ctrl_id;

	drv_phase = hs_timing_cfg[ctrl_id][timing].drv_phase;
	smpl_dly   = hs_timing_cfg[ctrl_id][timing].smpl_dly;
	if (smpl_phase == -1)
		smpl_phase = (hs_timing_cfg[ctrl_id][timing].smpl_phase_max +
			     hs_timing_cfg[ctrl_id][timing].smpl_phase_min) / 2;

	switch (timing) {
	case MMC_TIMING_UHS_SDR104:
		if (smpl_phase >= USE_DLY_MIN_SMPL &&
				smpl_phase <= USE_DLY_MAX_SMPL)
			use_smpl_dly = 1;
			/* fallthrough */
	case MMC_TIMING_UHS_SDR50:
		if (smpl_phase >= ENABLE_SHIFT_MIN_SMPL &&
				smpl_phase <= ENABLE_SHIFT_MAX_SMPL)
			enable_shift = 1;
		break;
	}

	mci_writel(host, GPIO, 0x0);
	usleep_range(5, 10);

	reg_value = FIELD_PREP(UHS_REG_EXT_SAMPLE_PHASE_MASK, smpl_phase) |
		    FIELD_PREP(UHS_REG_EXT_SAMPLE_DLY_MASK, smpl_dly) |
		    FIELD_PREP(UHS_REG_EXT_SAMPLE_DRVPHASE_MASK, drv_phase);
	mci_writel(host, UHS_REG_EXT, reg_value);

	mci_writel(host, ENABLE_SHIFT, enable_shift);

	reg_value = FIELD_PREP(GPIO_CLK_DIV_MASK, GENCLK_DIV) |
			     FIELD_PREP(GPIO_USE_SAMPLE_DLY_MASK, use_smpl_dly);
	mci_writel(host, GPIO, (unsigned int)reg_value | GPIO_CLK_ENABLE);

	/* We should delay 1ms wait for timing setting finished. */
	usleep_range(1000, 2000);
}