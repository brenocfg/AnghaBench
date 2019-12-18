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
typedef  int u16 ;
struct rt2x00_dev {struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int /*<<< orphan*/  txmixer_gain_5g; int /*<<< orphan*/  txmixer_gain_24g; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_EXT_LNA2 ; 
 int /*<<< orphan*/  EEPROM_EXT_LNA2_A1 ; 
 int /*<<< orphan*/  EEPROM_EXT_LNA2_A2 ; 
 int /*<<< orphan*/  EEPROM_FREQ ; 
 int /*<<< orphan*/  EEPROM_FREQ_LED_MODE ; 
 int /*<<< orphan*/  EEPROM_FREQ_LED_POLARITY ; 
 int /*<<< orphan*/  EEPROM_FREQ_OFFSET ; 
 int /*<<< orphan*/  EEPROM_LED_ACT_CONF ; 
 int /*<<< orphan*/  EEPROM_LED_AG_CONF ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY ; 
 int /*<<< orphan*/  EEPROM_LNA ; 
 int /*<<< orphan*/  EEPROM_LNA_A0 ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_RF_TYPE ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_RXPATH ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_TXPATH ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_ANT_DIVERSITY ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_BROADBAND_EXT_LNA ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_BT_COEXIST ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_BW40M_2G ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_BW40M_5G ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_BW40M_SB_2G ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_BW40M_SB_5G ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_CARDBUS_ACCEL ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_DAC_TEST ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_EXTERNAL_LNA_2G ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_EXTERNAL_LNA_5G ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_EXTERNAL_TX_ALC ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_HW_RADIO ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_INTERNAL_TX_ALC ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF1_WPS_PBC ; 
 int /*<<< orphan*/  EEPROM_RSSI_A ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2_LNA_A2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A2_OFFSET2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A_OFFSET0 ; 
 int /*<<< orphan*/  EEPROM_RSSI_A_OFFSET1 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2_LNA_A1 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG2_OFFSET2 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG_OFFSET0 ; 
 int /*<<< orphan*/  EEPROM_RSSI_BG_OFFSET1 ; 
 int LED_MODE_TXRX_ACTIVITY ; 
 int RF2820 ; 
 int /*<<< orphan*/  RT2860 ; 
 int /*<<< orphan*/  RT2872 ; 
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT3883 ; 
 int abs (int) ; 
 int* rt2800_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_eeprom_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_get_txmixer_gain_24g (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_get_txmixer_gain_5g (struct rt2x00_dev*) ; 
 int rt2800_read_eeprom (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_eeprom_dbg (struct rt2x00_dev*,char*,int) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00lib_set_mac_address (struct rt2x00_dev*,int*) ; 

__attribute__((used)) static int rt2800_validate_eeprom(struct rt2x00_dev *rt2x00dev)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u16 word;
	u8 *mac;
	u8 default_lna_gain;
	int retval;

	/*
	 * Read the EEPROM.
	 */
	retval = rt2800_read_eeprom(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Start validation of the data that has been read.
	 */
	mac = rt2800_eeprom_addr(rt2x00dev, EEPROM_MAC_ADDR_0);
	rt2x00lib_set_mac_address(rt2x00dev, mac);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_NIC_CONF0);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_NIC_CONF0_RXPATH, 2);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF0_TXPATH, 1);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF0_RF_TYPE, RF2820);
		rt2800_eeprom_write(rt2x00dev, EEPROM_NIC_CONF0, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	} else if (rt2x00_rt(rt2x00dev, RT2860) ||
		   rt2x00_rt(rt2x00dev, RT2872)) {
		/*
		 * There is a max of 2 RX streams for RT28x0 series
		 */
		if (rt2x00_get_field16(word, EEPROM_NIC_CONF0_RXPATH) > 2)
			rt2x00_set_field16(&word, EEPROM_NIC_CONF0_RXPATH, 2);
		rt2800_eeprom_write(rt2x00dev, EEPROM_NIC_CONF0, word);
	}

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_NIC_CONF1);
	if (word == 0xffff) {
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_HW_RADIO, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_EXTERNAL_TX_ALC, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_EXTERNAL_LNA_2G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_EXTERNAL_LNA_5G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_CARDBUS_ACCEL, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_SB_2G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_SB_5G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_WPS_PBC, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_2G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_5G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BROADBAND_EXT_LNA, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_ANT_DIVERSITY, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_INTERNAL_TX_ALC, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BT_COEXIST, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_DAC_TEST, 0);
		rt2800_eeprom_write(rt2x00dev, EEPROM_NIC_CONF1, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	}

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_FREQ);
	if ((word & 0x00ff) == 0x00ff) {
		rt2x00_set_field16(&word, EEPROM_FREQ_OFFSET, 0);
		rt2800_eeprom_write(rt2x00dev, EEPROM_FREQ, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Freq: 0x%04x\n", word);
	}
	if ((word & 0xff00) == 0xff00) {
		rt2x00_set_field16(&word, EEPROM_FREQ_LED_MODE,
				   LED_MODE_TXRX_ACTIVITY);
		rt2x00_set_field16(&word, EEPROM_FREQ_LED_POLARITY, 0);
		rt2800_eeprom_write(rt2x00dev, EEPROM_FREQ, word);
		rt2800_eeprom_write(rt2x00dev, EEPROM_LED_AG_CONF, 0x5555);
		rt2800_eeprom_write(rt2x00dev, EEPROM_LED_ACT_CONF, 0x2221);
		rt2800_eeprom_write(rt2x00dev, EEPROM_LED_POLARITY, 0xa9f8);
		rt2x00_eeprom_dbg(rt2x00dev, "Led Mode: 0x%04x\n", word);
	}

	/*
	 * During the LNA validation we are going to use
	 * lna0 as correct value. Note that EEPROM_LNA
	 * is never validated.
	 */
	word = rt2800_eeprom_read(rt2x00dev, EEPROM_LNA);
	default_lna_gain = rt2x00_get_field16(word, EEPROM_LNA_A0);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_RSSI_BG);
	if (abs(rt2x00_get_field16(word, EEPROM_RSSI_BG_OFFSET0)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_BG_OFFSET0, 0);
	if (abs(rt2x00_get_field16(word, EEPROM_RSSI_BG_OFFSET1)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_BG_OFFSET1, 0);
	rt2800_eeprom_write(rt2x00dev, EEPROM_RSSI_BG, word);

	drv_data->txmixer_gain_24g = rt2800_get_txmixer_gain_24g(rt2x00dev);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_RSSI_BG2);
	if (abs(rt2x00_get_field16(word, EEPROM_RSSI_BG2_OFFSET2)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_BG2_OFFSET2, 0);
	if (!rt2x00_rt(rt2x00dev, RT3593) &&
	    !rt2x00_rt(rt2x00dev, RT3883)) {
		if (rt2x00_get_field16(word, EEPROM_RSSI_BG2_LNA_A1) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_RSSI_BG2_LNA_A1) == 0xff)
			rt2x00_set_field16(&word, EEPROM_RSSI_BG2_LNA_A1,
					   default_lna_gain);
	}
	rt2800_eeprom_write(rt2x00dev, EEPROM_RSSI_BG2, word);

	drv_data->txmixer_gain_5g = rt2800_get_txmixer_gain_5g(rt2x00dev);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_RSSI_A);
	if (abs(rt2x00_get_field16(word, EEPROM_RSSI_A_OFFSET0)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_A_OFFSET0, 0);
	if (abs(rt2x00_get_field16(word, EEPROM_RSSI_A_OFFSET1)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_A_OFFSET1, 0);
	rt2800_eeprom_write(rt2x00dev, EEPROM_RSSI_A, word);

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_RSSI_A2);
	if (abs(rt2x00_get_field16(word, EEPROM_RSSI_A2_OFFSET2)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_A2_OFFSET2, 0);
	if (!rt2x00_rt(rt2x00dev, RT3593) &&
	    !rt2x00_rt(rt2x00dev, RT3883)) {
		if (rt2x00_get_field16(word, EEPROM_RSSI_A2_LNA_A2) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_RSSI_A2_LNA_A2) == 0xff)
			rt2x00_set_field16(&word, EEPROM_RSSI_A2_LNA_A2,
					   default_lna_gain);
	}
	rt2800_eeprom_write(rt2x00dev, EEPROM_RSSI_A2, word);

	if (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883)) {
		word = rt2800_eeprom_read(rt2x00dev, EEPROM_EXT_LNA2);
		if (rt2x00_get_field16(word, EEPROM_EXT_LNA2_A1) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_EXT_LNA2_A1) == 0xff)
			rt2x00_set_field16(&word, EEPROM_EXT_LNA2_A1,
					   default_lna_gain);
		if (rt2x00_get_field16(word, EEPROM_EXT_LNA2_A2) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_EXT_LNA2_A2) == 0xff)
			rt2x00_set_field16(&word, EEPROM_EXT_LNA2_A1,
					   default_lna_gain);
		rt2800_eeprom_write(rt2x00dev, EEPROM_EXT_LNA2, word);
	}

	return 0;
}