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
typedef  int u16 ;
struct rt2x00_dev {int /*<<< orphan*/  flags; } ;
struct ieee80211_channel {int band; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHANNEL_HT40 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_BYRATE ; 
 scalar_t__ TX_PWR_CFG_0 ; 
 int /*<<< orphan*/  TX_PWR_CFG_1 ; 
 int /*<<< orphan*/  TX_PWR_CFG_1B_48MBS ; 
 int /*<<< orphan*/  TX_PWR_CFG_2 ; 
 int /*<<< orphan*/  TX_PWR_CFG_2B_MCS6_MCS7 ; 
 int /*<<< orphan*/  TX_PWR_CFG_3 ; 
 int /*<<< orphan*/  TX_PWR_CFG_3B_MCS14 ; 
 int /*<<< orphan*/  TX_PWR_CFG_4 ; 
 int /*<<< orphan*/  TX_PWR_CFG_4B_STBC_MCS6 ; 
 scalar_t__ TX_PWR_CFG_7 ; 
 int /*<<< orphan*/  TX_PWR_CFG_7B_54MBS ; 
 int /*<<< orphan*/  TX_PWR_CFG_7B_MCS7 ; 
 scalar_t__ TX_PWR_CFG_8 ; 
 int /*<<< orphan*/  TX_PWR_CFG_8B_MCS15 ; 
 scalar_t__ TX_PWR_CFG_9 ; 
 int /*<<< orphan*/  TX_PWR_CFG_9B_STBC_MCS7 ; 
 int /*<<< orphan*/  rt2800_config_alc (struct rt2x00_dev*,struct ieee80211_channel*,int) ; 
 int rt2800_eeprom_read_from_array (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int rt2800_get_txpower_bw_comp (struct rt2x00_dev*,int) ; 
 int rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,scalar_t__,int) ; 
 int rt2x00_get_field32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2800_config_txpower_rt6352(struct rt2x00_dev *rt2x00dev,
					 struct ieee80211_channel *chan,
					 int power_level)
{
	u32 reg, pwreg;
	u16 eeprom;
	u32 data, gdata;
	u8 t, i;
	enum nl80211_band band = chan->band;
	int delta;

	/* Warn user if bw_comp is set in EEPROM */
	delta = rt2800_get_txpower_bw_comp(rt2x00dev, band);

	if (delta)
		rt2x00_warn(rt2x00dev, "ignoring EEPROM HT40 power delta: %d\n",
			    delta);

	/* populate TX_PWR_CFG_0 up to TX_PWR_CFG_4 from EEPROM for HT20, limit
	 * value to 0x3f and replace 0x20 by 0x21 as this is what the vendor
	 * driver does as well, though it looks kinda wrong.
	 * Maybe some misunderstanding of what a signed 8-bit value is? Maybe
	 * the hardware has a problem handling 0x20, and as the code initially
	 * used a fixed offset between HT20 and HT40 rates they had to work-
	 * around that issue and most likely just forgot about it later on.
	 * Maybe we should use rt2800_get_txpower_bw_comp() here as well,
	 * however, the corresponding EEPROM value is not respected by the
	 * vendor driver, so maybe this is rather being taken care of the
	 * TXALC and the driver doesn't need to handle it...?
	 * Though this is all very awkward, just do as they did, as that's what
	 * board vendors expected when they populated the EEPROM...
	 */
	for (i = 0; i < 5; i++) {
		eeprom = rt2800_eeprom_read_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       i * 2);

		data = eeprom;

		t = eeprom & 0x3f;
		if (t == 32)
			t++;

		gdata = t;

		t = (eeprom & 0x3f00) >> 8;
		if (t == 32)
			t++;

		gdata |= (t << 8);

		eeprom = rt2800_eeprom_read_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       (i * 2) + 1);

		t = eeprom & 0x3f;
		if (t == 32)
			t++;

		gdata |= (t << 16);

		t = (eeprom & 0x3f00) >> 8;
		if (t == 32)
			t++;

		gdata |= (t << 24);
		data |= (eeprom << 16);

		if (!test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags)) {
			/* HT20 */
			if (data != 0xffffffff)
				rt2800_register_write(rt2x00dev,
						      TX_PWR_CFG_0 + (i * 4),
						      data);
		} else {
			/* HT40 */
			if (gdata != 0xffffffff)
				rt2800_register_write(rt2x00dev,
						      TX_PWR_CFG_0 + (i * 4),
						      gdata);
		}
	}

	/* Aparently Ralink ran out of space in the BYRATE calibration section
	 * of the EERPOM which is copied to the corresponding TX_PWR_CFG_x
	 * registers. As recent 2T chips use 8-bit instead of 4-bit values for
	 * power-offsets more space would be needed. Ralink decided to keep the
	 * EEPROM layout untouched and rather have some shared values covering
	 * multiple bitrates.
	 * Populate the registers not covered by the EEPROM in the same way the
	 * vendor driver does.
	 */

	/* For OFDM 54MBS use value from OFDM 48MBS */
	pwreg = 0;
	reg = rt2800_register_read(rt2x00dev, TX_PWR_CFG_1);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_1B_48MBS);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_7B_54MBS, t);

	/* For MCS 7 use value from MCS 6 */
	reg = rt2800_register_read(rt2x00dev, TX_PWR_CFG_2);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_2B_MCS6_MCS7);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_7B_MCS7, t);
	rt2800_register_write(rt2x00dev, TX_PWR_CFG_7, pwreg);

	/* For MCS 15 use value from MCS 14 */
	pwreg = 0;
	reg = rt2800_register_read(rt2x00dev, TX_PWR_CFG_3);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_3B_MCS14);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_8B_MCS15, t);
	rt2800_register_write(rt2x00dev, TX_PWR_CFG_8, pwreg);

	/* For STBC MCS 7 use value from STBC MCS 6 */
	pwreg = 0;
	reg = rt2800_register_read(rt2x00dev, TX_PWR_CFG_4);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_4B_STBC_MCS6);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_9B_STBC_MCS7, t);
	rt2800_register_write(rt2x00dev, TX_PWR_CFG_9, pwreg);

	rt2800_config_alc(rt2x00dev, chan, power_level);

	/* TODO: temperature compensation code! */
}