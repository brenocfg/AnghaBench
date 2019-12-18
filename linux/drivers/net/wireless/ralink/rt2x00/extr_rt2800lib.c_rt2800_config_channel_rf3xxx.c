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
struct TYPE_2__ {int rx_chain_num; int tx_chain_num; } ;
struct rt2x00_dev {int freq_offset; TYPE_1__ default_ant; struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int calibration_bw40; int calibration_bw20; } ;
struct rf_channel {int rf1; int rf3; int rf2; } ;
struct ieee80211_conf {int dummy; } ;
struct channel_info {int default_power1; int default_power2; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCSR12_TX_POWER ; 
 int /*<<< orphan*/  RFCSR13_TX_POWER ; 
 int /*<<< orphan*/  RFCSR1_RX0_PD ; 
 int /*<<< orphan*/  RFCSR1_RX1_PD ; 
 int /*<<< orphan*/  RFCSR1_RX2_PD ; 
 int /*<<< orphan*/  RFCSR1_TX0_PD ; 
 int /*<<< orphan*/  RFCSR1_TX1_PD ; 
 int /*<<< orphan*/  RFCSR1_TX2_PD ; 
 int /*<<< orphan*/  RFCSR23_FREQ_OFFSET ; 
 int /*<<< orphan*/  RFCSR24_TX_CALIB ; 
 int /*<<< orphan*/  RFCSR30_RF_CALIBRATION ; 
 int /*<<< orphan*/  RFCSR31_RX_CALIB ; 
 int /*<<< orphan*/  RFCSR3_K ; 
 int /*<<< orphan*/  RFCSR6_R1 ; 
 int /*<<< orphan*/  RFCSR7_RF_TUNING ; 
 int /*<<< orphan*/  RT3390 ; 
 scalar_t__ conf_is_ht40 (struct ieee80211_conf*) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt2800_config_channel_rf3xxx(struct rt2x00_dev *rt2x00dev,
					 struct ieee80211_conf *conf,
					 struct rf_channel *rf,
					 struct channel_info *info)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 rfcsr, calib_tx, calib_rx;

	rt2800_rfcsr_write(rt2x00dev, 2, rf->rf1);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 3);
	rt2x00_set_field8(&rfcsr, RFCSR3_K, rf->rf3);
	rt2800_rfcsr_write(rt2x00dev, 3, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 6);
	rt2x00_set_field8(&rfcsr, RFCSR6_R1, rf->rf2);
	rt2800_rfcsr_write(rt2x00dev, 6, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 12);
	rt2x00_set_field8(&rfcsr, RFCSR12_TX_POWER, info->default_power1);
	rt2800_rfcsr_write(rt2x00dev, 12, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 13);
	rt2x00_set_field8(&rfcsr, RFCSR13_TX_POWER, info->default_power2);
	rt2800_rfcsr_write(rt2x00dev, 13, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD,
			  rt2x00dev->default_ant.rx_chain_num <= 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD,
			  rt2x00dev->default_ant.rx_chain_num <= 2);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD,
			  rt2x00dev->default_ant.tx_chain_num <= 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD,
			  rt2x00dev->default_ant.tx_chain_num <= 2);
	rt2800_rfcsr_write(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 23);
	rt2x00_set_field8(&rfcsr, RFCSR23_FREQ_OFFSET, rt2x00dev->freq_offset);
	rt2800_rfcsr_write(rt2x00dev, 23, rfcsr);

	if (rt2x00_rt(rt2x00dev, RT3390)) {
		calib_tx = conf_is_ht40(conf) ? 0x68 : 0x4f;
		calib_rx = conf_is_ht40(conf) ? 0x6f : 0x4f;
	} else {
		if (conf_is_ht40(conf)) {
			calib_tx = drv_data->calibration_bw40;
			calib_rx = drv_data->calibration_bw40;
		} else {
			calib_tx = drv_data->calibration_bw20;
			calib_rx = drv_data->calibration_bw20;
		}
	}

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 24);
	rt2x00_set_field8(&rfcsr, RFCSR24_TX_CALIB, calib_tx);
	rt2800_rfcsr_write(rt2x00dev, 24, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 31);
	rt2x00_set_field8(&rfcsr, RFCSR31_RX_CALIB, calib_rx);
	rt2800_rfcsr_write(rt2x00dev, 31, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 7);
	rt2x00_set_field8(&rfcsr, RFCSR7_RF_TUNING, 1);
	rt2800_rfcsr_write(rt2x00dev, 7, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 30);
	rt2x00_set_field8(&rfcsr, RFCSR30_RF_CALIBRATION, 1);
	rt2800_rfcsr_write(rt2x00dev, 30, rfcsr);

	usleep_range(1000, 1500);

	rt2x00_set_field8(&rfcsr, RFCSR30_RF_CALIBRATION, 0);
	rt2800_rfcsr_write(rt2x00dev, 30, rfcsr);
}