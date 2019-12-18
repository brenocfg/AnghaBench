#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_11__ {int rf; } ;
struct TYPE_13__ {unsigned int tx_chain_num; unsigned int rx_chain_num; } ;
struct TYPE_9__ {unsigned int tx_params; int* rx_mask; } ;
struct TYPE_12__ {int ht_supported; int cap; int ampdu_factor; int ampdu_density; TYPE_1__ mcs; } ;
struct hw_mode_spec {int supported_rates; int num_channels; struct channel_info* channels_info; TYPE_4__ ht; int /*<<< orphan*/  supported_bands; void* channels; } ;
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; TYPE_3__ chip; TYPE_5__ default_ant; TYPE_6__* hw; int /*<<< orphan*/  dev; struct hw_mode_spec spec; } ;
struct channel_info {char default_power1; char default_power2; char default_power3; } ;
struct TYPE_14__ {int max_rates; int max_report_rates; int max_rate_tries; TYPE_2__* wiphy; } ;
struct TYPE_10__ {int retry_short; int retry_long; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CAPABILITY_VCO_RECALIBRATION ; 
 int /*<<< orphan*/  EEPROM_EXT_TXPOWER_A3 ; 
 int /*<<< orphan*/  EEPROM_EXT_TXPOWER_BG3 ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_A1 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_A2 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_BG1 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_BG2 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOST_BROADCAST_PS_BUFFERING ; 
 int IEEE80211_HT_CAP_GRN_FLD ; 
 unsigned int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 unsigned int IEEE80211_HT_CAP_TX_STBC ; 
 unsigned int IEEE80211_HT_MCS_TX_DEFINED ; 
 unsigned int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 unsigned int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int /*<<< orphan*/  MAC_DEBUG_INDEX ; 
 int /*<<< orphan*/  MAC_DEBUG_INDEX_XTAL ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 int /*<<< orphan*/  PS_NULLFUNC_STACK ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
#define  RF2020 151 
#define  RF2720 150 
#define  RF2750 149 
#define  RF2820 148 
#define  RF2850 147 
#define  RF3020 146 
#define  RF3021 145 
#define  RF3022 144 
#define  RF3052 143 
#define  RF3053 142 
#define  RF3070 141 
#define  RF3290 140 
#define  RF3320 139 
#define  RF3322 138 
#define  RF3853 137 
#define  RF5350 136 
#define  RF5360 135 
#define  RF5362 134 
#define  RF5370 133 
#define  RF5372 132 
#define  RF5390 131 
#define  RF5392 130 
#define  RF5592 129 
#define  RF7620 128 
 int /*<<< orphan*/  SET_IEEE80211_DEV (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  SUPPORT_BAND_2GHZ ; 
 int /*<<< orphan*/  SUPPORT_BAND_5GHZ ; 
 int SUPPORT_RATE_CCK ; 
 int SUPPORT_RATE_OFDM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_hw_set (TYPE_6__*,int /*<<< orphan*/ ) ; 
 struct channel_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* rf_vals ; 
 void* rf_vals_3853 ; 
 void* rf_vals_3x ; 
 void* rf_vals_3x_xtal20 ; 
 void* rf_vals_5592_xtal20 ; 
 void* rf_vals_5592_xtal40 ; 
 void* rf_vals_7620 ; 
 int /*<<< orphan*/  rt2800_clk_is_20mhz (struct rt2x00_dev*) ; 
 char* rt2800_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2800_hwcrypt_disabled (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_is_usb (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_rf (struct rt2x00_dev*,int const) ; 

__attribute__((used)) static int rt2800_probe_hw_mode(struct rt2x00_dev *rt2x00dev)
{
	struct hw_mode_spec *spec = &rt2x00dev->spec;
	struct channel_info *info;
	char *default_power1;
	char *default_power2;
	char *default_power3;
	unsigned int i, tx_chains, rx_chains;
	u32 reg;

	/*
	 * Disable powersaving as default.
	 */
	rt2x00dev->hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	/*
	 * Change default retry settings to values corresponding more closely
	 * to rate[0].count setting of minstrel rate control algorithm.
	 */
	rt2x00dev->hw->wiphy->retry_short = 2;
	rt2x00dev->hw->wiphy->retry_long = 2;

	/*
	 * Initialize all hw fields.
	 */
	ieee80211_hw_set(rt2x00dev->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(rt2x00dev->hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(rt2x00dev->hw, PS_NULLFUNC_STACK);
	ieee80211_hw_set(rt2x00dev->hw, SIGNAL_DBM);
	ieee80211_hw_set(rt2x00dev->hw, SUPPORTS_PS);

	/*
	 * Don't set IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING for USB devices
	 * unless we are capable of sending the buffered frames out after the
	 * DTIM transmission using rt2x00lib_beacondone. This will send out
	 * multicast and broadcast traffic immediately instead of buffering it
	 * infinitly and thus dropping it after some time.
	 */
	if (!rt2x00_is_usb(rt2x00dev))
		ieee80211_hw_set(rt2x00dev->hw, HOST_BROADCAST_PS_BUFFERING);

	/* Set MFP if HW crypto is disabled. */
	if (rt2800_hwcrypt_disabled(rt2x00dev))
		ieee80211_hw_set(rt2x00dev->hw, MFP_CAPABLE);

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2800_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * As rt2800 has a global fallback table we cannot specify
	 * more then one tx rate per frame but since the hw will
	 * try several rates (based on the fallback table) we should
	 * initialize max_report_rates to the maximum number of rates
	 * we are going to try. Otherwise mac80211 will truncate our
	 * reported tx rates and the rc algortihm will end up with
	 * incorrect data.
	 */
	rt2x00dev->hw->max_rates = 1;
	rt2x00dev->hw->max_report_rates = 7;
	rt2x00dev->hw->max_rate_tries = 1;

	/*
	 * Initialize hw_mode information.
	 */
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	switch (rt2x00dev->chip.rf) {
	case RF2720:
	case RF2820:
		spec->num_channels = 14;
		spec->channels = rf_vals;
		break;

	case RF2750:
	case RF2850:
		spec->num_channels = ARRAY_SIZE(rf_vals);
		spec->channels = rf_vals;
		break;

	case RF2020:
	case RF3020:
	case RF3021:
	case RF3022:
	case RF3070:
	case RF3290:
	case RF3320:
	case RF3322:
	case RF5350:
	case RF5360:
	case RF5362:
	case RF5370:
	case RF5372:
	case RF5390:
	case RF5392:
		spec->num_channels = 14;
		if (rt2800_clk_is_20mhz(rt2x00dev))
			spec->channels = rf_vals_3x_xtal20;
		else
			spec->channels = rf_vals_3x;
		break;

	case RF7620:
		spec->num_channels = ARRAY_SIZE(rf_vals_7620);
		spec->channels = rf_vals_7620;
		break;

	case RF3052:
	case RF3053:
		spec->num_channels = ARRAY_SIZE(rf_vals_3x);
		spec->channels = rf_vals_3x;
		break;

	case RF3853:
		spec->num_channels = ARRAY_SIZE(rf_vals_3853);
		spec->channels = rf_vals_3853;
		break;

	case RF5592:
		reg = rt2800_register_read(rt2x00dev, MAC_DEBUG_INDEX);
		if (rt2x00_get_field32(reg, MAC_DEBUG_INDEX_XTAL)) {
			spec->num_channels = ARRAY_SIZE(rf_vals_5592_xtal40);
			spec->channels = rf_vals_5592_xtal40;
		} else {
			spec->num_channels = ARRAY_SIZE(rf_vals_5592_xtal20);
			spec->channels = rf_vals_5592_xtal20;
		}
		break;
	}

	if (WARN_ON_ONCE(!spec->channels))
		return -ENODEV;

	spec->supported_bands = SUPPORT_BAND_2GHZ;
	if (spec->num_channels > 14)
		spec->supported_bands |= SUPPORT_BAND_5GHZ;

	/*
	 * Initialize HT information.
	 */
	if (!rt2x00_rf(rt2x00dev, RF2020))
		spec->ht.ht_supported = true;
	else
		spec->ht.ht_supported = false;

	spec->ht.cap =
	    IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	    IEEE80211_HT_CAP_GRN_FLD |
	    IEEE80211_HT_CAP_SGI_20 |
	    IEEE80211_HT_CAP_SGI_40;

	tx_chains = rt2x00dev->default_ant.tx_chain_num;
	rx_chains = rt2x00dev->default_ant.rx_chain_num;

	if (tx_chains >= 2)
		spec->ht.cap |= IEEE80211_HT_CAP_TX_STBC;

	spec->ht.cap |= rx_chains << IEEE80211_HT_CAP_RX_STBC_SHIFT;

	spec->ht.ampdu_factor = (rx_chains > 1) ? 3 : 2;
	spec->ht.ampdu_density = 4;
	spec->ht.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	if (tx_chains != rx_chains) {
		spec->ht.mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		spec->ht.mcs.tx_params |=
		    (tx_chains - 1) << IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;
	}

	switch (rx_chains) {
	case 3:
		spec->ht.mcs.rx_mask[2] = 0xff;
		/* fall through */
	case 2:
		spec->ht.mcs.rx_mask[1] = 0xff;
		/* fall through */
	case 1:
		spec->ht.mcs.rx_mask[0] = 0xff;
		spec->ht.mcs.rx_mask[4] = 0x1; /* MCS32 */
		break;
	}

	/*
	 * Create channel information array
	 */
	info = kcalloc(spec->num_channels, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	spec->channels_info = info;

	default_power1 = rt2800_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_BG1);
	default_power2 = rt2800_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_BG2);

	if (rt2x00dev->default_ant.tx_chain_num > 2)
		default_power3 = rt2800_eeprom_addr(rt2x00dev,
						    EEPROM_EXT_TXPOWER_BG3);
	else
		default_power3 = NULL;

	for (i = 0; i < 14; i++) {
		info[i].default_power1 = default_power1[i];
		info[i].default_power2 = default_power2[i];
		if (default_power3)
			info[i].default_power3 = default_power3[i];
	}

	if (spec->num_channels > 14) {
		default_power1 = rt2800_eeprom_addr(rt2x00dev,
						    EEPROM_TXPOWER_A1);
		default_power2 = rt2800_eeprom_addr(rt2x00dev,
						    EEPROM_TXPOWER_A2);

		if (rt2x00dev->default_ant.tx_chain_num > 2)
			default_power3 =
				rt2800_eeprom_addr(rt2x00dev,
						   EEPROM_EXT_TXPOWER_A3);
		else
			default_power3 = NULL;

		for (i = 14; i < spec->num_channels; i++) {
			info[i].default_power1 = default_power1[i - 14];
			info[i].default_power2 = default_power2[i - 14];
			if (default_power3)
				info[i].default_power3 = default_power3[i - 14];
		}
	}

	switch (rt2x00dev->chip.rf) {
	case RF2020:
	case RF3020:
	case RF3021:
	case RF3022:
	case RF3320:
	case RF3052:
	case RF3053:
	case RF3070:
	case RF3290:
	case RF3853:
	case RF5350:
	case RF5360:
	case RF5362:
	case RF5370:
	case RF5372:
	case RF5390:
	case RF5392:
	case RF5592:
	case RF7620:
		__set_bit(CAPABILITY_VCO_RECALIBRATION, &rt2x00dev->cap_flags);
		break;
	}

	return 0;
}