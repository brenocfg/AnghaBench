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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;
struct rt2x00_dev {int /*<<< orphan*/  curr_band; TYPE_1__ default_ant; } ;
struct antenna_setup {int tx_chain_num; int rx_chain_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTENNA_B ; 
 int /*<<< orphan*/  BBP1_TX_ANTENNA ; 
 int /*<<< orphan*/  BBP3_RX_ADC ; 
 int /*<<< orphan*/  BBP3_RX_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_ANT_DIVERSITY ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  RT3352 ; 
 int /*<<< orphan*/  RT3390 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT3883 ; 
 int rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_config_3572bt_ant (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_set_ant_diversity (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_has_cap_bt_coexist (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

void rt2800_config_ant(struct rt2x00_dev *rt2x00dev, struct antenna_setup *ant)
{
	u8 r1;
	u8 r3;
	u16 eeprom;

	r1 = rt2800_bbp_read(rt2x00dev, 1);
	r3 = rt2800_bbp_read(rt2x00dev, 3);

	if (rt2x00_rt(rt2x00dev, RT3572) &&
	    rt2x00_has_cap_bt_coexist(rt2x00dev))
		rt2800_config_3572bt_ant(rt2x00dev);

	/*
	 * Configure the TX antenna.
	 */
	switch (ant->tx_chain_num) {
	case 1:
		rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 0);
		break;
	case 2:
		if (rt2x00_rt(rt2x00dev, RT3572) &&
		    rt2x00_has_cap_bt_coexist(rt2x00dev))
			rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 1);
		else
			rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 2);
		break;
	case 3:
		rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 2);
		break;
	}

	/*
	 * Configure the RX antenna.
	 */
	switch (ant->rx_chain_num) {
	case 1:
		if (rt2x00_rt(rt2x00dev, RT3070) ||
		    rt2x00_rt(rt2x00dev, RT3090) ||
		    rt2x00_rt(rt2x00dev, RT3352) ||
		    rt2x00_rt(rt2x00dev, RT3390)) {
			eeprom = rt2800_eeprom_read(rt2x00dev,
						    EEPROM_NIC_CONF1);
			if (rt2x00_get_field16(eeprom,
						EEPROM_NIC_CONF1_ANT_DIVERSITY))
				rt2800_set_ant_diversity(rt2x00dev,
						rt2x00dev->default_ant.rx);
		}
		rt2x00_set_field8(&r3, BBP3_RX_ANTENNA, 0);
		break;
	case 2:
		if (rt2x00_rt(rt2x00dev, RT3572) &&
		    rt2x00_has_cap_bt_coexist(rt2x00dev)) {
			rt2x00_set_field8(&r3, BBP3_RX_ADC, 1);
			rt2x00_set_field8(&r3, BBP3_RX_ANTENNA,
				rt2x00dev->curr_band == NL80211_BAND_5GHZ);
			rt2800_set_ant_diversity(rt2x00dev, ANTENNA_B);
		} else {
			rt2x00_set_field8(&r3, BBP3_RX_ANTENNA, 1);
		}
		break;
	case 3:
		rt2x00_set_field8(&r3, BBP3_RX_ANTENNA, 2);
		break;
	}

	rt2800_bbp_write(rt2x00dev, 3, r3);
	rt2800_bbp_write(rt2x00dev, 1, r1);

	if (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883)) {
		if (ant->rx_chain_num == 1)
			rt2800_bbp_write(rt2x00dev, 86, 0x00);
		else
			rt2800_bbp_write(rt2x00dev, 86, 0x46);
	}
}