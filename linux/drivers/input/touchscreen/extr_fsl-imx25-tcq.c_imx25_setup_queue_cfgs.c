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
struct mx25_tcq_priv {int sample_count; int /*<<< orphan*/  core_regs; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MX25_ADCQ_CFG (int /*<<< orphan*/ ) ; 
 int MX25_ADCQ_CFG_IGS ; 
 int MX25_ADCQ_CFG_IN_XP ; 
 int MX25_ADCQ_CFG_IN_YP ; 
 int MX25_ADCQ_CFG_NOS (int) ; 
 int MX25_ADCQ_CFG_REFN_XN ; 
 int MX25_ADCQ_CFG_REFN_YN ; 
 int MX25_ADCQ_CFG_REFP_XP ; 
 int MX25_ADCQ_CFG_REFP_YP ; 
 int MX25_ADCQ_CFG_SETTLING_TIME (unsigned int) ; 
 int MX25_ADCQ_CFG_XNUR_LOW ; 
 int MX25_ADCQ_CFG_XNUR_OFF ; 
 int MX25_ADCQ_CFG_XPUL_HIGH ; 
 int MX25_ADCQ_CFG_XPUL_OFF ; 
 int MX25_ADCQ_CFG_YNLR ; 
 int MX25_ADCQ_CFG_YPLL_HIGH ; 
 int MX25_ADCQ_CFG_YPLL_OFF ; 
 int /*<<< orphan*/  MX25_CFG_PRECHARGE ; 
 int /*<<< orphan*/  MX25_CFG_TOUCH_DETECT ; 
 int /*<<< orphan*/  MX25_CFG_X_MEASUREMENT ; 
 int /*<<< orphan*/  MX25_CFG_Y_MEASUREMENT ; 
 int MX25_PRECHARGE_VALUE ; 
 int MX25_TOUCH_DETECT_VALUE ; 
 int /*<<< orphan*/  MX25_TSC_TICR ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imx25_setup_queue_cfgs(struct mx25_tcq_priv *priv,
				   unsigned int settling_cnt)
{
	u32 precharge_cfg =
			MX25_PRECHARGE_VALUE |
			MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt);
	u32 touch_detect_cfg =
			MX25_TOUCH_DETECT_VALUE |
			MX25_ADCQ_CFG_NOS(1) |
			MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt);

	regmap_write(priv->core_regs, MX25_TSC_TICR, precharge_cfg);

	/* PRECHARGE */
	regmap_write(priv->regs, MX25_ADCQ_CFG(MX25_CFG_PRECHARGE),
		     precharge_cfg);

	/* TOUCH_DETECT */
	regmap_write(priv->regs, MX25_ADCQ_CFG(MX25_CFG_TOUCH_DETECT),
		     touch_detect_cfg);

	/* X Measurement */
	regmap_write(priv->regs, MX25_ADCQ_CFG(MX25_CFG_X_MEASUREMENT),
		     MX25_ADCQ_CFG_YPLL_OFF |
		     MX25_ADCQ_CFG_XNUR_LOW |
		     MX25_ADCQ_CFG_XPUL_HIGH |
		     MX25_ADCQ_CFG_REFP_XP |
		     MX25_ADCQ_CFG_IN_YP |
		     MX25_ADCQ_CFG_REFN_XN |
		     MX25_ADCQ_CFG_NOS(priv->sample_count) |
		     MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt));

	/* Y Measurement */
	regmap_write(priv->regs, MX25_ADCQ_CFG(MX25_CFG_Y_MEASUREMENT),
		     MX25_ADCQ_CFG_YNLR |
		     MX25_ADCQ_CFG_YPLL_HIGH |
		     MX25_ADCQ_CFG_XNUR_OFF |
		     MX25_ADCQ_CFG_XPUL_OFF |
		     MX25_ADCQ_CFG_REFP_YP |
		     MX25_ADCQ_CFG_IN_XP |
		     MX25_ADCQ_CFG_REFN_YN |
		     MX25_ADCQ_CFG_NOS(priv->sample_count) |
		     MX25_ADCQ_CFG_SETTLING_TIME(settling_cnt));

	/* Enable the touch detection right now */
	regmap_write(priv->core_regs, MX25_TSC_TICR, touch_detect_cfg |
		     MX25_ADCQ_CFG_IGS);
}