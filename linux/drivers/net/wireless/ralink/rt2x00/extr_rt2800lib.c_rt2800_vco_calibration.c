#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int tx_chain_num; int rx_chain_num; } ;
struct TYPE_3__ {int rf; } ;
struct rt2x00_dev {int rf_channel; TYPE_2__ default_ant; TYPE_1__ chip; } ;

/* Variables and functions */
#define  RF2020 146 
#define  RF3020 145 
#define  RF3021 144 
#define  RF3022 143 
#define  RF3052 142 
#define  RF3053 141 
#define  RF3070 140 
#define  RF3290 139 
#define  RF3320 138 
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
 int /*<<< orphan*/  RFCSR3_VCOCAL_EN ; 
 int /*<<< orphan*/  RFCSR4_VCOCAL_EN ; 
 int /*<<< orphan*/  RFCSR7_RF_TUNING ; 
 int /*<<< orphan*/  RT6352 ; 
 int /*<<< orphan*/  TX_PIN_CFG ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_A0_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_A1_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_A2_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_DISABLE ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_G0_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_G1_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_G2_EN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_has_cap_external_lna_bg (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void rt2800_vco_calibration(struct rt2x00_dev *rt2x00dev)
{
	u32	tx_pin;
	u8	rfcsr;
	unsigned long min_sleep = 0;

	/*
	 * A voltage-controlled oscillator(VCO) is an electronic oscillator
	 * designed to be controlled in oscillation frequency by a voltage
	 * input. Maybe the temperature will affect the frequency of
	 * oscillation to be shifted. The VCO calibration will be called
	 * periodically to adjust the frequency to be precision.
	*/

	tx_pin = rt2800_register_read(rt2x00dev, TX_PIN_CFG);
	tx_pin &= TX_PIN_CFG_PA_PE_DISABLE;
	rt2800_register_write(rt2x00dev, TX_PIN_CFG, tx_pin);

	switch (rt2x00dev->chip.rf) {
	case RF2020:
	case RF3020:
	case RF3021:
	case RF3022:
	case RF3320:
	case RF3052:
		rfcsr = rt2800_rfcsr_read(rt2x00dev, 7);
		rt2x00_set_field8(&rfcsr, RFCSR7_RF_TUNING, 1);
		rt2800_rfcsr_write(rt2x00dev, 7, rfcsr);
		break;
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
		rfcsr = rt2800_rfcsr_read(rt2x00dev, 3);
		rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
		rt2800_rfcsr_write(rt2x00dev, 3, rfcsr);
		min_sleep = 1000;
		break;
	case RF7620:
		rt2800_rfcsr_write(rt2x00dev, 5, 0x40);
		rt2800_rfcsr_write(rt2x00dev, 4, 0x0C);
		rfcsr = rt2800_rfcsr_read(rt2x00dev, 4);
		rt2x00_set_field8(&rfcsr, RFCSR4_VCOCAL_EN, 1);
		rt2800_rfcsr_write(rt2x00dev, 4, rfcsr);
		min_sleep = 2000;
		break;
	default:
		WARN_ONCE(1, "Not supported RF chipset %x for VCO recalibration",
			  rt2x00dev->chip.rf);
		return;
	}

	if (min_sleep > 0)
		usleep_range(min_sleep, min_sleep * 2);

	tx_pin = rt2800_register_read(rt2x00dev, TX_PIN_CFG);
	if (rt2x00dev->rf_channel <= 14) {
		switch (rt2x00dev->default_ant.tx_chain_num) {
		case 3:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G2_EN, 1);
			/* fall through */
		case 2:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G1_EN, 1);
			/* fall through */
		case 1:
		default:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN, 1);
			break;
		}
	} else {
		switch (rt2x00dev->default_ant.tx_chain_num) {
		case 3:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A2_EN, 1);
			/* fall through */
		case 2:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A1_EN, 1);
			/* fall through */
		case 1:
		default:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A0_EN, 1);
			break;
		}
	}
	rt2800_register_write(rt2x00dev, TX_PIN_CFG, tx_pin);

	if (rt2x00_rt(rt2x00dev, RT6352)) {
		if (rt2x00dev->default_ant.rx_chain_num == 1) {
			rt2800_bbp_write(rt2x00dev, 91, 0x07);
			rt2800_bbp_write(rt2x00dev, 95, 0x1A);
			rt2800_bbp_write(rt2x00dev, 195, 128);
			rt2800_bbp_write(rt2x00dev, 196, 0xA0);
			rt2800_bbp_write(rt2x00dev, 195, 170);
			rt2800_bbp_write(rt2x00dev, 196, 0x12);
			rt2800_bbp_write(rt2x00dev, 195, 171);
			rt2800_bbp_write(rt2x00dev, 196, 0x10);
		} else {
			rt2800_bbp_write(rt2x00dev, 91, 0x06);
			rt2800_bbp_write(rt2x00dev, 95, 0x9A);
			rt2800_bbp_write(rt2x00dev, 195, 128);
			rt2800_bbp_write(rt2x00dev, 196, 0xE0);
			rt2800_bbp_write(rt2x00dev, 195, 170);
			rt2800_bbp_write(rt2x00dev, 196, 0x30);
			rt2800_bbp_write(rt2x00dev, 195, 171);
			rt2800_bbp_write(rt2x00dev, 196, 0x30);
		}

		if (rt2x00_has_cap_external_lna_bg(rt2x00dev)) {
			rt2800_bbp_write(rt2x00dev, 75, 0x68);
			rt2800_bbp_write(rt2x00dev, 76, 0x4C);
			rt2800_bbp_write(rt2x00dev, 79, 0x1C);
			rt2800_bbp_write(rt2x00dev, 80, 0x0C);
			rt2800_bbp_write(rt2x00dev, 82, 0xB6);
		}

		/* On 11A, We should delay and wait RF/BBP to be stable
		 * and the appropriate time should be 1000 micro seconds
		 * 2005/06/05 - On 11G, we also need this delay time.
		 * Otherwise it's difficult to pass the WHQL.
		 */
		usleep_range(1000, 1500);
	}
}