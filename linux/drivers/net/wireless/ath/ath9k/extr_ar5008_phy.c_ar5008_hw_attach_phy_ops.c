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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw_private_ops {int /*<<< orphan*/  compute_pll_control; int /*<<< orphan*/  ani_cache_ini_regs; int /*<<< orphan*/  ani_control; int /*<<< orphan*/  set_radar_params; int /*<<< orphan*/  do_getnf; int /*<<< orphan*/  restore_chainmask; int /*<<< orphan*/  rfbus_done; int /*<<< orphan*/  rfbus_req; int /*<<< orphan*/  set_delta_slope; int /*<<< orphan*/  mark_phy_inactive; int /*<<< orphan*/  set_rfmode; int /*<<< orphan*/  process_ini; int /*<<< orphan*/  init_bb; int /*<<< orphan*/  set_channel_regs; int /*<<< orphan*/  set_rf_regs; int /*<<< orphan*/  spur_mitigate_freq; int /*<<< orphan*/  rf_set_freq; } ;
struct ath_hw {int /*<<< orphan*/  nf_regs; } ;

/* Variables and functions */
#define  AR_PHY_CCA 133 
#define  AR_PHY_CH1_CCA 132 
#define  AR_PHY_CH1_EXT_CCA 131 
#define  AR_PHY_CH2_CCA 130 
#define  AR_PHY_CH2_EXT_CCA 129 
#define  AR_PHY_EXT_CCA 128 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9160_10_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  ar5008_hw_ani_cache_ini_regs ; 
 int /*<<< orphan*/  ar5008_hw_ani_control_new ; 
 int /*<<< orphan*/  ar5008_hw_compute_pll_control ; 
 int /*<<< orphan*/  ar5008_hw_do_getnf ; 
 int /*<<< orphan*/  ar5008_hw_init_bb ; 
 int /*<<< orphan*/  ar5008_hw_mark_phy_inactive ; 
 int /*<<< orphan*/  ar5008_hw_process_ini ; 
 int ar5008_hw_rf_alloc_ext_banks (struct ath_hw*) ; 
 int /*<<< orphan*/  ar5008_hw_rfbus_done ; 
 int /*<<< orphan*/  ar5008_hw_rfbus_req ; 
 int /*<<< orphan*/  ar5008_hw_set_channel ; 
 int /*<<< orphan*/  ar5008_hw_set_channel_regs ; 
 int /*<<< orphan*/  ar5008_hw_set_delta_slope ; 
 int /*<<< orphan*/  ar5008_hw_set_nf_limits (struct ath_hw*) ; 
 int /*<<< orphan*/  ar5008_hw_set_radar_conf (struct ath_hw*) ; 
 int /*<<< orphan*/  ar5008_hw_set_radar_params ; 
 int /*<<< orphan*/  ar5008_hw_set_rf_regs ; 
 int /*<<< orphan*/  ar5008_hw_set_rfmode ; 
 int /*<<< orphan*/  ar5008_hw_spur_mitigate ; 
 int /*<<< orphan*/  ar5008_restore_chainmask ; 
 int /*<<< orphan*/  ar9160_hw_compute_pll_control ; 
 struct ath_hw_private_ops* ath9k_hw_private_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int ar5008_hw_attach_phy_ops(struct ath_hw *ah)
{
	struct ath_hw_private_ops *priv_ops = ath9k_hw_private_ops(ah);
	static const u32 ar5416_cca_regs[6] = {
		AR_PHY_CCA,
		AR_PHY_CH1_CCA,
		AR_PHY_CH2_CCA,
		AR_PHY_EXT_CCA,
		AR_PHY_CH1_EXT_CCA,
		AR_PHY_CH2_EXT_CCA
	};
	int ret;

	ret = ar5008_hw_rf_alloc_ext_banks(ah);
	if (ret)
	    return ret;

	priv_ops->rf_set_freq = ar5008_hw_set_channel;
	priv_ops->spur_mitigate_freq = ar5008_hw_spur_mitigate;

	priv_ops->set_rf_regs = ar5008_hw_set_rf_regs;
	priv_ops->set_channel_regs = ar5008_hw_set_channel_regs;
	priv_ops->init_bb = ar5008_hw_init_bb;
	priv_ops->process_ini = ar5008_hw_process_ini;
	priv_ops->set_rfmode = ar5008_hw_set_rfmode;
	priv_ops->mark_phy_inactive = ar5008_hw_mark_phy_inactive;
	priv_ops->set_delta_slope = ar5008_hw_set_delta_slope;
	priv_ops->rfbus_req = ar5008_hw_rfbus_req;
	priv_ops->rfbus_done = ar5008_hw_rfbus_done;
	priv_ops->restore_chainmask = ar5008_restore_chainmask;
	priv_ops->do_getnf = ar5008_hw_do_getnf;
	priv_ops->set_radar_params = ar5008_hw_set_radar_params;

	priv_ops->ani_control = ar5008_hw_ani_control_new;
	priv_ops->ani_cache_ini_regs = ar5008_hw_ani_cache_ini_regs;

	if (AR_SREV_9100(ah) || AR_SREV_9160_10_OR_LATER(ah))
		priv_ops->compute_pll_control = ar9160_hw_compute_pll_control;
	else
		priv_ops->compute_pll_control = ar5008_hw_compute_pll_control;

	ar5008_hw_set_nf_limits(ah);
	ar5008_hw_set_radar_conf(ah);
	memcpy(ah->nf_regs, ar5416_cca_regs, sizeof(ah->nf_regs));
	return 0;
}