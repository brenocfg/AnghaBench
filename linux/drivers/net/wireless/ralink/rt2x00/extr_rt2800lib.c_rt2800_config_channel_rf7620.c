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
struct TYPE_2__ {int tx_chain_num; int rx_chain_num; } ;
struct rt2x00_dev {int /*<<< orphan*/  flags; TYPE_1__ default_ant; struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int rx_calibration_bw40; int tx_calibration_bw40; int rx_calibration_bw20; int tx_calibration_bw20; } ;
struct rf_channel {int rf1; int rf2; int rf3; int rf4; int channel; } ;
struct ieee80211_conf {int dummy; } ;
struct channel_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_SCANNING ; 
 int /*<<< orphan*/  RFCSR13_RDIV_MT7620 ; 
 int /*<<< orphan*/  RFCSR16_RF_PLL_FREQ_SEL_MT7620 ; 
 int /*<<< orphan*/  RFCSR16_SDM_MODE_MT7620 ; 
 int /*<<< orphan*/  RFCSR19_K ; 
 int /*<<< orphan*/  RFCSR1_TX2_EN_MT7620 ; 
 int /*<<< orphan*/  RFCSR21_BIT1 ; 
 int /*<<< orphan*/  RFCSR21_BIT8 ; 
 int /*<<< orphan*/  RFCSR22_FREQPLAN_D_MT7620 ; 
 int /*<<< orphan*/  RFCSR28_CH11_HT40 ; 
 int /*<<< orphan*/  RFCSR2_RX2_EN_MT7620 ; 
 int /*<<< orphan*/  RFCSR2_TX2_EN_MT7620 ; 
 int /*<<< orphan*/  RFCSR42_TX2_EN_MT7620 ; 
 scalar_t__ conf_is_ht40 (struct ieee80211_conf*) ; 
 scalar_t__ rt2800_clk_is_20mhz (struct rt2x00_dev*) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int rt2800_rfcsr_read_bank (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write_bank (struct rt2x00_dev*,int,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write_dccal (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2800_config_channel_rf7620(struct rt2x00_dev *rt2x00dev,
					 struct ieee80211_conf *conf,
					 struct rf_channel *rf,
					 struct channel_info *info)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 rx_agc_fc, tx_agc_fc;
	u8 rfcsr;

	/* Frequeny plan setting */
	/* Rdiv setting (set 0x03 if Xtal==20)
	 * R13[1:0]
	 */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 13);
	rt2x00_set_field8(&rfcsr, RFCSR13_RDIV_MT7620,
			  rt2800_clk_is_20mhz(rt2x00dev) ? 3 : 0);
	rt2800_rfcsr_write(rt2x00dev, 13, rfcsr);

	/* N setting
	 * R20[7:0] in rf->rf1
	 * R21[0] always 0
	 */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 20);
	rfcsr = (rf->rf1 & 0x00ff);
	rt2800_rfcsr_write(rt2x00dev, 20, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 21);
	rt2x00_set_field8(&rfcsr, RFCSR21_BIT1, 0);
	rt2800_rfcsr_write(rt2x00dev, 21, rfcsr);

	/* K setting (always 0)
	 * R16[3:0] (RF PLL freq selection)
	 */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 16);
	rt2x00_set_field8(&rfcsr, RFCSR16_RF_PLL_FREQ_SEL_MT7620, 0);
	rt2800_rfcsr_write(rt2x00dev, 16, rfcsr);

	/* D setting (always 0)
	 * R22[2:0] (D=15, R22[2:0]=<111>)
	 */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 22);
	rt2x00_set_field8(&rfcsr, RFCSR22_FREQPLAN_D_MT7620, 0);
	rt2800_rfcsr_write(rt2x00dev, 22, rfcsr);

	/* Ksd setting
	 * Ksd: R17<7:0> in rf->rf2
	 *      R18<7:0> in rf->rf3
	 *      R19<1:0> in rf->rf4
	 */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 17);
	rfcsr = rf->rf2;
	rt2800_rfcsr_write(rt2x00dev, 17, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 18);
	rfcsr = rf->rf3;
	rt2800_rfcsr_write(rt2x00dev, 18, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 19);
	rt2x00_set_field8(&rfcsr, RFCSR19_K, rf->rf4);
	rt2800_rfcsr_write(rt2x00dev, 19, rfcsr);

	/* Default: XO=20MHz , SDM mode */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 16);
	rt2x00_set_field8(&rfcsr, RFCSR16_SDM_MODE_MT7620, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 16, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 21);
	rt2x00_set_field8(&rfcsr, RFCSR21_BIT8, 1);
	rt2800_rfcsr_write(rt2x00dev, 21, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_EN_MT7620,
			  rt2x00dev->default_ant.tx_chain_num != 1);
	rt2800_rfcsr_write(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 2);
	rt2x00_set_field8(&rfcsr, RFCSR2_TX2_EN_MT7620,
			  rt2x00dev->default_ant.tx_chain_num != 1);
	rt2x00_set_field8(&rfcsr, RFCSR2_RX2_EN_MT7620,
			  rt2x00dev->default_ant.rx_chain_num != 1);
	rt2800_rfcsr_write(rt2x00dev, 2, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 42);
	rt2x00_set_field8(&rfcsr, RFCSR42_TX2_EN_MT7620,
			  rt2x00dev->default_ant.tx_chain_num != 1);
	rt2800_rfcsr_write(rt2x00dev, 42, rfcsr);

	/* RF for DC Cal BW */
	if (conf_is_ht40(conf)) {
		rt2800_rfcsr_write_dccal(rt2x00dev, 6, 0x10);
		rt2800_rfcsr_write_dccal(rt2x00dev, 7, 0x10);
		rt2800_rfcsr_write_dccal(rt2x00dev, 8, 0x04);
		rt2800_rfcsr_write_dccal(rt2x00dev, 58, 0x10);
		rt2800_rfcsr_write_dccal(rt2x00dev, 59, 0x10);
	} else {
		rt2800_rfcsr_write_dccal(rt2x00dev, 6, 0x20);
		rt2800_rfcsr_write_dccal(rt2x00dev, 7, 0x20);
		rt2800_rfcsr_write_dccal(rt2x00dev, 8, 0x00);
		rt2800_rfcsr_write_dccal(rt2x00dev, 58, 0x20);
		rt2800_rfcsr_write_dccal(rt2x00dev, 59, 0x20);
	}

	if (conf_is_ht40(conf)) {
		rt2800_rfcsr_write_dccal(rt2x00dev, 58, 0x08);
		rt2800_rfcsr_write_dccal(rt2x00dev, 59, 0x08);
	} else {
		rt2800_rfcsr_write_dccal(rt2x00dev, 58, 0x28);
		rt2800_rfcsr_write_dccal(rt2x00dev, 59, 0x28);
	}

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 28);
	rt2x00_set_field8(&rfcsr, RFCSR28_CH11_HT40,
			  conf_is_ht40(conf) && (rf->channel == 11));
	rt2800_rfcsr_write(rt2x00dev, 28, rfcsr);

	if (!test_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags)) {
		if (conf_is_ht40(conf)) {
			rx_agc_fc = drv_data->rx_calibration_bw40;
			tx_agc_fc = drv_data->tx_calibration_bw40;
		} else {
			rx_agc_fc = drv_data->rx_calibration_bw20;
			tx_agc_fc = drv_data->tx_calibration_bw20;
		}
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 5, 6);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 5, 6, rfcsr);
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 5, 7);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 5, 7, rfcsr);
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 7, 6);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 7, 6, rfcsr);
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 7, 7);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 7, 7, rfcsr);

		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 5, 58);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 5, 58, rfcsr);
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 5, 59);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 5, 59, rfcsr);
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 7, 58);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 7, 58, rfcsr);
		rfcsr = rt2800_rfcsr_read_bank(rt2x00dev, 7, 59);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_write_bank(rt2x00dev, 7, 59, rfcsr);
	}
}