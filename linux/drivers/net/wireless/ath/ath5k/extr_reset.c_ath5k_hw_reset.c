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
typedef  int u8 ;
typedef  int u32 ;
struct ieee80211_channel {int hw_value; int center_freq; } ;
struct ath5k_hw {scalar_t__ ah_radio; scalar_t__ ah_version; scalar_t__ ah_mac_srev; scalar_t__ ah_use_32khz_clock; int /*<<< orphan*/ * ah_rf_banks; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 scalar_t__ AR5K_AR5211 ; 
 scalar_t__ AR5K_AR5212 ; 
 int /*<<< orphan*/  AR5K_BEACON ; 
 int /*<<< orphan*/  AR5K_BEACON_ENABLE ; 
 int /*<<< orphan*/  AR5K_GPIOCR ; 
 int /*<<< orphan*/  AR5K_GPIODO ; 
#define  AR5K_MODE_11A 130 
#define  AR5K_MODE_11B 129 
#define  AR5K_MODE_11G 128 
 int /*<<< orphan*/  AR5K_PCICFG ; 
 int AR5K_PCICFG_LEDSTATE ; 
 int /*<<< orphan*/  AR5K_PHY (int /*<<< orphan*/ ) ; 
 int AR5K_PHY_SHIFT_5GHZ ; 
 int /*<<< orphan*/  AR5K_QUEUE_DCU_SEQNUM (int) ; 
 int /*<<< orphan*/  AR5K_REG_DISABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_RF2413 ; 
 scalar_t__ AR5K_RF5112 ; 
 scalar_t__ AR5K_RF5413 ; 
 scalar_t__ AR5K_SREV_AR5211 ; 
 int /*<<< orphan*/  AR5K_TSF_L32 ; 
 int /*<<< orphan*/  AR5K_TSF_U32 ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,...) ; 
 int EINVAL ; 
 int NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  ath5k_hw_commit_eeprom_settings (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ath5k_hw_dma_init (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_gainf_calibrate (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_init_core_clock (struct ath5k_hw*) ; 
 int ath5k_hw_init_queues (struct ath5k_hw*) ; 
 int ath5k_hw_nic_wakeup (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ath5k_hw_pcu_init (struct ath5k_hw*,int) ; 
 int ath5k_hw_phy_init (struct ath5k_hw*,struct ieee80211_channel*,int,int) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reset_tsf (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_sleep_clock (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_tweak_initval_settings (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int ath5k_hw_write_initvals (struct ath5k_hw*,int,int) ; 

int
ath5k_hw_reset(struct ath5k_hw *ah, enum nl80211_iftype op_mode,
		struct ieee80211_channel *channel, bool fast, bool skip_pcu)
{
	u32 s_seq[10], s_led[3], tsf_up, tsf_lo;
	u8 mode;
	int i, ret;

	tsf_up = 0;
	tsf_lo = 0;
	mode = 0;

	/*
	 * Sanity check for fast flag
	 * Fast channel change only available
	 * on AR2413/AR5413.
	 */
	if (fast && (ah->ah_radio != AR5K_RF2413) &&
	(ah->ah_radio != AR5K_RF5413))
		fast = false;

	/* Disable sleep clock operation
	 * to avoid register access delay on certain
	 * PHY registers */
	if (ah->ah_version == AR5K_AR5212)
		ath5k_hw_set_sleep_clock(ah, false);

	mode = channel->hw_value;
	switch (mode) {
	case AR5K_MODE_11A:
		break;
	case AR5K_MODE_11G:
		if (ah->ah_version <= AR5K_AR5211) {
			ATH5K_ERR(ah,
				"G mode not available on 5210/5211");
			return -EINVAL;
		}
		break;
	case AR5K_MODE_11B:
		if (ah->ah_version < AR5K_AR5211) {
			ATH5K_ERR(ah,
				"B mode not available on 5210");
			return -EINVAL;
		}
		break;
	default:
		ATH5K_ERR(ah,
			"invalid channel: %d\n", channel->center_freq);
		return -EINVAL;
	}

	/*
	 * If driver requested fast channel change and DMA has stopped
	 * go on. If it fails continue with a normal reset.
	 */
	if (fast) {
		ret = ath5k_hw_phy_init(ah, channel, mode, true);
		if (ret) {
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				"fast chan change failed, falling back to normal reset\n");
			/* Non fatal, can happen eg.
			 * on mode change */
			ret = 0;
		} else {
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				"fast chan change successful\n");
			return 0;
		}
	}

	/*
	 * Save some registers before a reset
	 */
	if (ah->ah_version != AR5K_AR5210) {
		/*
		 * Save frame sequence count
		 * For revs. after Oahu, only save
		 * seq num for DCU 0 (Global seq num)
		 */
		if (ah->ah_mac_srev < AR5K_SREV_AR5211) {

			for (i = 0; i < 10; i++)
				s_seq[i] = ath5k_hw_reg_read(ah,
					AR5K_QUEUE_DCU_SEQNUM(i));

		} else {
			s_seq[0] = ath5k_hw_reg_read(ah,
					AR5K_QUEUE_DCU_SEQNUM(0));
		}

		/* TSF accelerates on AR5211 during reset
		 * As a workaround save it here and restore
		 * it later so that it's back in time after
		 * reset. This way it'll get re-synced on the
		 * next beacon without breaking ad-hoc.
		 *
		 * On AR5212 TSF is almost preserved across a
		 * reset so it stays back in time anyway and
		 * we don't have to save/restore it.
		 *
		 * XXX: Since this breaks power saving we have
		 * to disable power saving until we receive the
		 * next beacon, so we can resync beacon timers */
		if (ah->ah_version == AR5K_AR5211) {
			tsf_up = ath5k_hw_reg_read(ah, AR5K_TSF_U32);
			tsf_lo = ath5k_hw_reg_read(ah, AR5K_TSF_L32);
		}
	}


	/*GPIOs*/
	s_led[0] = ath5k_hw_reg_read(ah, AR5K_PCICFG) &
					AR5K_PCICFG_LEDSTATE;
	s_led[1] = ath5k_hw_reg_read(ah, AR5K_GPIOCR);
	s_led[2] = ath5k_hw_reg_read(ah, AR5K_GPIODO);


	/*
	 * Since we are going to write rf buffer
	 * check if we have any pending gain_F
	 * optimization settings
	 */
	if (ah->ah_version == AR5K_AR5212 &&
	(ah->ah_radio <= AR5K_RF5112)) {
		if (!fast && ah->ah_rf_banks != NULL)
				ath5k_hw_gainf_calibrate(ah);
	}

	/* Wakeup the device */
	ret = ath5k_hw_nic_wakeup(ah, channel);
	if (ret)
		return ret;

	/* PHY access enable */
	if (ah->ah_mac_srev >= AR5K_SREV_AR5211)
		ath5k_hw_reg_write(ah, AR5K_PHY_SHIFT_5GHZ, AR5K_PHY(0));
	else
		ath5k_hw_reg_write(ah, AR5K_PHY_SHIFT_5GHZ | 0x40,
							AR5K_PHY(0));

	/* Write initial settings */
	ret = ath5k_hw_write_initvals(ah, mode, skip_pcu);
	if (ret)
		return ret;

	/* Initialize core clock settings */
	ath5k_hw_init_core_clock(ah);

	/*
	 * Tweak initval settings for revised
	 * chipsets and add some more config
	 * bits
	 */
	ath5k_hw_tweak_initval_settings(ah, channel);

	/* Commit values from EEPROM */
	ath5k_hw_commit_eeprom_settings(ah, channel);


	/*
	 * Restore saved values
	 */

	/* Seqnum, TSF */
	if (ah->ah_version != AR5K_AR5210) {
		if (ah->ah_mac_srev < AR5K_SREV_AR5211) {
			for (i = 0; i < 10; i++)
				ath5k_hw_reg_write(ah, s_seq[i],
					AR5K_QUEUE_DCU_SEQNUM(i));
		} else {
			ath5k_hw_reg_write(ah, s_seq[0],
				AR5K_QUEUE_DCU_SEQNUM(0));
		}

		if (ah->ah_version == AR5K_AR5211) {
			ath5k_hw_reg_write(ah, tsf_up, AR5K_TSF_U32);
			ath5k_hw_reg_write(ah, tsf_lo, AR5K_TSF_L32);
		}
	}

	/* Ledstate */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, s_led[0]);

	/* Gpio settings */
	ath5k_hw_reg_write(ah, s_led[1], AR5K_GPIOCR);
	ath5k_hw_reg_write(ah, s_led[2], AR5K_GPIODO);

	/*
	 * Initialize PCU
	 */
	ath5k_hw_pcu_init(ah, op_mode);

	/*
	 * Initialize PHY
	 */
	ret = ath5k_hw_phy_init(ah, channel, mode, false);
	if (ret) {
		ATH5K_ERR(ah,
			"failed to initialize PHY (%i) !\n", ret);
		return ret;
	}

	/*
	 * Configure QCUs/DCUs
	 */
	ret = ath5k_hw_init_queues(ah);
	if (ret)
		return ret;


	/*
	 * Initialize DMA/Interrupts
	 */
	ath5k_hw_dma_init(ah);


	/*
	 * Enable 32KHz clock function for AR5212+ chips
	 * Set clocks to 32KHz operation and use an
	 * external 32KHz crystal when sleeping if one
	 * exists.
	 * Disabled by default because it is also disabled in
	 * other drivers and it is known to cause stability
	 * issues on some devices
	 */
	if (ah->ah_use_32khz_clock && ah->ah_version == AR5K_AR5212 &&
	    op_mode != NL80211_IFTYPE_AP)
		ath5k_hw_set_sleep_clock(ah, true);

	/*
	 * Disable beacons and reset the TSF
	 */
	AR5K_REG_DISABLE_BITS(ah, AR5K_BEACON, AR5K_BEACON_ENABLE);
	ath5k_hw_reset_tsf(ah);
	return 0;
}