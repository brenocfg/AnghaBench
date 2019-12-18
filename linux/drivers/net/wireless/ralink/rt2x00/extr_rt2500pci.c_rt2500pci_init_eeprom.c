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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ rx; scalar_t__ tx; } ;
struct rt2x00_dev {scalar_t__ rssi_offset; int /*<<< orphan*/  cap_flags; int /*<<< orphan*/  led_qual; int /*<<< orphan*/  led_radio; TYPE_1__ default_ant; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_HW_BUTTON ; 
 int /*<<< orphan*/  CAPABILITY_LINK_TUNING ; 
 int /*<<< orphan*/  CSR0 ; 
 int /*<<< orphan*/  CSR0_REVISION ; 
 int /*<<< orphan*/  EEPROM_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_HARDWARE_RADIO ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_LED_MODE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RF_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_TX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_CALIBRATE_OFFSET ; 
 int /*<<< orphan*/  EEPROM_CALIBRATE_OFFSET_RSSI ; 
 int /*<<< orphan*/  EEPROM_NIC ; 
 int /*<<< orphan*/  EEPROM_NIC_DYN_BBP_TUNE ; 
 int ENODEV ; 
 scalar_t__ LED_MODE_ASUS ; 
 scalar_t__ LED_MODE_DEFAULT ; 
 scalar_t__ LED_MODE_TXRX_ACTIVITY ; 
 int /*<<< orphan*/  LED_TYPE_ACTIVITY ; 
 int /*<<< orphan*/  LED_TYPE_RADIO ; 
 int /*<<< orphan*/  REQUIRE_DELAYED_RFKILL ; 
 int /*<<< orphan*/  RF2522 ; 
 int /*<<< orphan*/  RF2523 ; 
 int /*<<< orphan*/  RF2524 ; 
 int /*<<< orphan*/  RF2525 ; 
 int /*<<< orphan*/  RF2525E ; 
 int /*<<< orphan*/  RF5222 ; 
 int /*<<< orphan*/  RT2560 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500pci_init_led (struct rt2x00_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 scalar_t__ rt2x00_get_field16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_chip (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500pci_init_eeprom(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;
	u16 value;
	u16 eeprom;

	/*
	 * Read EEPROM word for configuration.
	 */
	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_ANTENNA);

	/*
	 * Identify RF chipset.
	 */
	value = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RF_TYPE);
	reg = rt2x00mmio_register_read(rt2x00dev, CSR0);
	rt2x00_set_chip(rt2x00dev, RT2560, value,
			rt2x00_get_field32(reg, CSR0_REVISION));

	if (!rt2x00_rf(rt2x00dev, RF2522) &&
	    !rt2x00_rf(rt2x00dev, RF2523) &&
	    !rt2x00_rf(rt2x00dev, RF2524) &&
	    !rt2x00_rf(rt2x00dev, RF2525) &&
	    !rt2x00_rf(rt2x00dev, RF2525E) &&
	    !rt2x00_rf(rt2x00dev, RF5222)) {
		rt2x00_err(rt2x00dev, "Invalid RF chipset detected\n");
		return -ENODEV;
	}

	/*
	 * Identify default antenna configuration.
	 */
	rt2x00dev->default_ant.tx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_TX_DEFAULT);
	rt2x00dev->default_ant.rx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RX_DEFAULT);

	/*
	 * Store led mode, for correct led behaviour.
	 */
#ifdef CONFIG_RT2X00_LIB_LEDS
	value = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_LED_MODE);

	rt2500pci_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	if (value == LED_MODE_TXRX_ACTIVITY ||
	    value == LED_MODE_DEFAULT ||
	    value == LED_MODE_ASUS)
		rt2500pci_init_led(rt2x00dev, &rt2x00dev->led_qual,
				   LED_TYPE_ACTIVITY);
#endif /* CONFIG_RT2X00_LIB_LEDS */

	/*
	 * Detect if this device has an hardware controlled radio.
	 */
	if (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO)) {
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);
		/*
		 * On this device RFKILL initialized during probe does not work.
		 */
		__set_bit(REQUIRE_DELAYED_RFKILL, &rt2x00dev->cap_flags);
	}

	/*
	 * Check if the BBP tuning should be enabled.
	 */
	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC);
	if (!rt2x00_get_field16(eeprom, EEPROM_NIC_DYN_BBP_TUNE))
		__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);

	/*
	 * Read the RSSI <-> dBm offset information.
	 */
	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_CALIBRATE_OFFSET);
	rt2x00dev->rssi_offset =
	    rt2x00_get_field16(eeprom, EEPROM_CALIBRATE_OFFSET_RSSI);

	return 0;
}