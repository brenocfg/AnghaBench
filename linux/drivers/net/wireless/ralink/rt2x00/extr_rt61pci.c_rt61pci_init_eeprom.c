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
typedef  int u16 ;
struct TYPE_2__ {int tx; int rx; } ;
struct rt2x00_dev {int freq_offset; int /*<<< orphan*/  led_mcu_reg; int /*<<< orphan*/  led_qual; int /*<<< orphan*/  led_assoc; int /*<<< orphan*/  led_radio; TYPE_1__ default_ant; int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int ANTENNA_A ; 
 int ANTENNA_B ; 
 void* ANTENNA_SW_DIVERSITY ; 
 int /*<<< orphan*/  CAPABILITY_DOUBLE_ANTENNA ; 
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_A ; 
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_BG ; 
 int /*<<< orphan*/  CAPABILITY_FRAME_TYPE ; 
 int /*<<< orphan*/  CAPABILITY_HW_BUTTON ; 
 int /*<<< orphan*/  CAPABILITY_RF_SEQUENCE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_FRAME_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_HARDWARE_RADIO ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_NUM ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RF_TYPE ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_RX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_ANTENNA_TX_DEFAULT ; 
 int /*<<< orphan*/  EEPROM_FREQ ; 
 int /*<<< orphan*/  EEPROM_FREQ_OFFSET ; 
 int /*<<< orphan*/  EEPROM_FREQ_SEQ ; 
 int /*<<< orphan*/  EEPROM_LED ; 
 int /*<<< orphan*/  EEPROM_LED_LED_MODE ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_ACT ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_GPIO_0 ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_GPIO_1 ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_GPIO_2 ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_GPIO_3 ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_GPIO_4 ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_RDY_A ; 
 int /*<<< orphan*/  EEPROM_LED_POLARITY_RDY_G ; 
 int /*<<< orphan*/  EEPROM_NIC ; 
 int /*<<< orphan*/  EEPROM_NIC_ENABLE_DIVERSITY ; 
 int /*<<< orphan*/  EEPROM_NIC_EXTERNAL_LNA_A ; 
 int /*<<< orphan*/  EEPROM_NIC_EXTERNAL_LNA_BG ; 
 int /*<<< orphan*/  EEPROM_NIC_RX_FIXED ; 
 int /*<<< orphan*/  EEPROM_NIC_TX_DIVERSITY ; 
 int /*<<< orphan*/  EEPROM_NIC_TX_FIXED ; 
 int ENODEV ; 
 int LED_MODE_SIGNAL_STRENGTH ; 
 int /*<<< orphan*/  LED_TYPE_ASSOC ; 
 int /*<<< orphan*/  LED_TYPE_QUALITY ; 
 int /*<<< orphan*/  LED_TYPE_RADIO ; 
 int /*<<< orphan*/  MAC_CSR0 ; 
 int /*<<< orphan*/  MAC_CSR0_CHIPSET ; 
 int /*<<< orphan*/  MAC_CSR0_REVISION ; 
 int /*<<< orphan*/  MCU_LEDCS_LED_MODE ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_ACT ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_GPIO_0 ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_GPIO_1 ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_GPIO_2 ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_GPIO_3 ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_GPIO_4 ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_READY_A ; 
 int /*<<< orphan*/  MCU_LEDCS_POLARITY_READY_BG ; 
 int /*<<< orphan*/  RF2527 ; 
 int /*<<< orphan*/  RF2529 ; 
 int /*<<< orphan*/  RF5225 ; 
 int /*<<< orphan*/  RF5325 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_has_cap_double_antenna (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_chip (struct rt2x00_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt61pci_init_led (struct rt2x00_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt61pci_init_eeprom(struct rt2x00_dev *rt2x00dev)
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
	reg = rt2x00mmio_register_read(rt2x00dev, MAC_CSR0);
	rt2x00_set_chip(rt2x00dev, rt2x00_get_field32(reg, MAC_CSR0_CHIPSET),
			value, rt2x00_get_field32(reg, MAC_CSR0_REVISION));

	if (!rt2x00_rf(rt2x00dev, RF5225) &&
	    !rt2x00_rf(rt2x00dev, RF5325) &&
	    !rt2x00_rf(rt2x00dev, RF2527) &&
	    !rt2x00_rf(rt2x00dev, RF2529)) {
		rt2x00_err(rt2x00dev, "Invalid RF chipset detected\n");
		return -ENODEV;
	}

	/*
	 * Determine number of antennas.
	 */
	if (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_NUM) == 2)
		__set_bit(CAPABILITY_DOUBLE_ANTENNA, &rt2x00dev->cap_flags);

	/*
	 * Identify default antenna configuration.
	 */
	rt2x00dev->default_ant.tx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_TX_DEFAULT);
	rt2x00dev->default_ant.rx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RX_DEFAULT);

	/*
	 * Read the Frame type.
	 */
	if (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_FRAME_TYPE))
		__set_bit(CAPABILITY_FRAME_TYPE, &rt2x00dev->cap_flags);

	/*
	 * Detect if this device has a hardware controlled radio.
	 */
	if (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Read frequency offset and RF programming sequence.
	 */
	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_FREQ);
	if (rt2x00_get_field16(eeprom, EEPROM_FREQ_SEQ))
		__set_bit(CAPABILITY_RF_SEQUENCE, &rt2x00dev->cap_flags);

	rt2x00dev->freq_offset = rt2x00_get_field16(eeprom, EEPROM_FREQ_OFFSET);

	/*
	 * Read external LNA informations.
	 */
	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_NIC);

	if (rt2x00_get_field16(eeprom, EEPROM_NIC_EXTERNAL_LNA_A))
		__set_bit(CAPABILITY_EXTERNAL_LNA_A, &rt2x00dev->cap_flags);
	if (rt2x00_get_field16(eeprom, EEPROM_NIC_EXTERNAL_LNA_BG))
		__set_bit(CAPABILITY_EXTERNAL_LNA_BG, &rt2x00dev->cap_flags);

	/*
	 * When working with a RF2529 chip without double antenna,
	 * the antenna settings should be gathered from the NIC
	 * eeprom word.
	 */
	if (rt2x00_rf(rt2x00dev, RF2529) &&
	    !rt2x00_has_cap_double_antenna(rt2x00dev)) {
		rt2x00dev->default_ant.rx =
		    ANTENNA_A + rt2x00_get_field16(eeprom, EEPROM_NIC_RX_FIXED);
		rt2x00dev->default_ant.tx =
		    ANTENNA_B - rt2x00_get_field16(eeprom, EEPROM_NIC_TX_FIXED);

		if (rt2x00_get_field16(eeprom, EEPROM_NIC_TX_DIVERSITY))
			rt2x00dev->default_ant.tx = ANTENNA_SW_DIVERSITY;
		if (rt2x00_get_field16(eeprom, EEPROM_NIC_ENABLE_DIVERSITY))
			rt2x00dev->default_ant.rx = ANTENNA_SW_DIVERSITY;
	}

	/*
	 * Store led settings, for correct led behaviour.
	 * If the eeprom value is invalid,
	 * switch to default led mode.
	 */
#ifdef CONFIG_RT2X00_LIB_LEDS
	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_LED);
	value = rt2x00_get_field16(eeprom, EEPROM_LED_LED_MODE);

	rt61pci_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	rt61pci_init_led(rt2x00dev, &rt2x00dev->led_assoc, LED_TYPE_ASSOC);
	if (value == LED_MODE_SIGNAL_STRENGTH)
		rt61pci_init_led(rt2x00dev, &rt2x00dev->led_qual,
				 LED_TYPE_QUALITY);

	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_LED_MODE, value);
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_0,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_0));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_1,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_1));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_2,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_2));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_3,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_3));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_4,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_4));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_ACT,
			   rt2x00_get_field16(eeprom, EEPROM_LED_POLARITY_ACT));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_READY_BG,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_RDY_G));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_READY_A,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_RDY_A));
#endif /* CONFIG_RT2X00_LIB_LEDS */

	return 0;
}