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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int txmixer_gain_24g; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP138_RX_ADC1 ; 
 int /*<<< orphan*/  BBP138_TX_DAC1 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0 ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_RXPATH ; 
 int /*<<< orphan*/  EEPROM_NIC_CONF0_TXPATH ; 
 int /*<<< orphan*/  REV_RT3070F ; 
 int /*<<< orphan*/  REV_RT3071E ; 
 int /*<<< orphan*/  REV_RT3090E ; 
 int /*<<< orphan*/  REV_RT3390E ; 
 int /*<<< orphan*/  RFCSR15_TX_LO2_EN ; 
 int /*<<< orphan*/  RFCSR17_R ; 
 int /*<<< orphan*/  RFCSR17_TXMIXER_GAIN ; 
 int /*<<< orphan*/  RFCSR17_TX_LO1_EN ; 
 int /*<<< orphan*/  RFCSR1_RF_BLOCK_EN ; 
 int /*<<< orphan*/  RFCSR1_RX0_PD ; 
 int /*<<< orphan*/  RFCSR1_RX1_PD ; 
 int /*<<< orphan*/  RFCSR1_TX0_PD ; 
 int /*<<< orphan*/  RFCSR1_TX1_PD ; 
 int /*<<< orphan*/  RFCSR20_RX_LO1_EN ; 
 int /*<<< orphan*/  RFCSR21_RX_LO2_EN ; 
 int /*<<< orphan*/  RFCSR27_R1 ; 
 int /*<<< orphan*/  RFCSR27_R2 ; 
 int /*<<< orphan*/  RFCSR27_R3 ; 
 int /*<<< orphan*/  RFCSR27_R4 ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3071 ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  RT3390 ; 
 int rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_has_cap_external_lna_bg (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev_lt (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_normal_mode_setup_3xxx(struct rt2x00_dev *rt2x00dev)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 min_gain, rfcsr, bbp;
	u16 eeprom;

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 17);

	rt2x00_set_field8(&rfcsr, RFCSR17_TX_LO1_EN, 0);
	if (rt2x00_rt(rt2x00dev, RT3070) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3390, REV_RT3390E)) {
		if (!rt2x00_has_cap_external_lna_bg(rt2x00dev))
			rt2x00_set_field8(&rfcsr, RFCSR17_R, 1);
	}

	min_gain = rt2x00_rt(rt2x00dev, RT3070) ? 1 : 2;
	if (drv_data->txmixer_gain_24g >= min_gain) {
		rt2x00_set_field8(&rfcsr, RFCSR17_TXMIXER_GAIN,
				  drv_data->txmixer_gain_24g);
	}

	rt2800_rfcsr_write(rt2x00dev, 17, rfcsr);

	if (rt2x00_rt(rt2x00dev, RT3090)) {
		/*  Turn off unused DAC1 and ADC1 to reduce power consumption */
		bbp = rt2800_bbp_read(rt2x00dev, 138);
		eeprom = rt2800_eeprom_read(rt2x00dev, EEPROM_NIC_CONF0);
		if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH) == 1)
			rt2x00_set_field8(&bbp, BBP138_RX_ADC1, 0);
		if (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) == 1)
			rt2x00_set_field8(&bbp, BBP138_TX_DAC1, 1);
		rt2800_bbp_write(rt2x00dev, 138, bbp);
	}

	if (rt2x00_rt(rt2x00dev, RT3070)) {
		rfcsr = rt2800_rfcsr_read(rt2x00dev, 27);
		if (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F))
			rt2x00_set_field8(&rfcsr, RFCSR27_R1, 3);
		else
			rt2x00_set_field8(&rfcsr, RFCSR27_R1, 0);
		rt2x00_set_field8(&rfcsr, RFCSR27_R2, 0);
		rt2x00_set_field8(&rfcsr, RFCSR27_R3, 0);
		rt2x00_set_field8(&rfcsr, RFCSR27_R4, 0);
		rt2800_rfcsr_write(rt2x00dev, 27, rfcsr);
	} else if (rt2x00_rt(rt2x00dev, RT3071) ||
		   rt2x00_rt(rt2x00dev, RT3090) ||
		   rt2x00_rt(rt2x00dev, RT3390)) {
		rfcsr = rt2800_rfcsr_read(rt2x00dev, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
		rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
		rt2800_rfcsr_write(rt2x00dev, 1, rfcsr);

		rfcsr = rt2800_rfcsr_read(rt2x00dev, 15);
		rt2x00_set_field8(&rfcsr, RFCSR15_TX_LO2_EN, 0);
		rt2800_rfcsr_write(rt2x00dev, 15, rfcsr);

		rfcsr = rt2800_rfcsr_read(rt2x00dev, 20);
		rt2x00_set_field8(&rfcsr, RFCSR20_RX_LO1_EN, 0);
		rt2800_rfcsr_write(rt2x00dev, 20, rfcsr);

		rfcsr = rt2800_rfcsr_read(rt2x00dev, 21);
		rt2x00_set_field8(&rfcsr, RFCSR21_RX_LO2_EN, 0);
		rt2800_rfcsr_write(rt2x00dev, 21, rfcsr);
	}
}