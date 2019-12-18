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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int calibration_bw20; int calibration_bw40; void* bbp26; void* bbp25; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_SWITCH ; 
 int /*<<< orphan*/  GPIO_SWITCH_4 ; 
 int /*<<< orphan*/  GPIO_SWITCH_7 ; 
 int /*<<< orphan*/  LDO_CFG0 ; 
 int /*<<< orphan*/  LDO_CFG0_BGSEL ; 
 int /*<<< orphan*/  LDO_CFG0_LDO_CORE_VLEVEL ; 
 int /*<<< orphan*/  RFCSR18_XO_TUNE_BYPASS ; 
 int /*<<< orphan*/  RFCSR2_RESCAL_EN ; 
 void* rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_freq_cal_mode1 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_3593 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt3593_post_bbp_init (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_3593(struct rt2x00_dev *rt2x00dev)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u32 reg;
	u8 rfcsr;

	/* Disable GPIO #4 and #7 function for LAN PE control */
	reg = rt2800_register_read(rt2x00dev, GPIO_SWITCH);
	rt2x00_set_field32(&reg, GPIO_SWITCH_4, 0);
	rt2x00_set_field32(&reg, GPIO_SWITCH_7, 0);
	rt2800_register_write(rt2x00dev, GPIO_SWITCH, reg);

	/* Initialize default register values */
	rt2800_rfcsr_write(rt2x00dev, 1, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 8, 0xf1);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 10, 0xd3);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x4e);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x12);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 32, 0x78);
	rt2800_rfcsr_write(rt2x00dev, 33, 0x3b);
	rt2800_rfcsr_write(rt2x00dev, 34, 0x3c);
	rt2800_rfcsr_write(rt2x00dev, 35, 0xe0);
	rt2800_rfcsr_write(rt2x00dev, 38, 0x86);
	rt2800_rfcsr_write(rt2x00dev, 39, 0x23);
	rt2800_rfcsr_write(rt2x00dev, 44, 0xd3);
	rt2800_rfcsr_write(rt2x00dev, 45, 0xbb);
	rt2800_rfcsr_write(rt2x00dev, 46, 0x60);
	rt2800_rfcsr_write(rt2x00dev, 49, 0x8e);
	rt2800_rfcsr_write(rt2x00dev, 50, 0x86);
	rt2800_rfcsr_write(rt2x00dev, 51, 0x75);
	rt2800_rfcsr_write(rt2x00dev, 52, 0x45);
	rt2800_rfcsr_write(rt2x00dev, 53, 0x18);
	rt2800_rfcsr_write(rt2x00dev, 54, 0x18);
	rt2800_rfcsr_write(rt2x00dev, 55, 0x18);
	rt2800_rfcsr_write(rt2x00dev, 56, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 57, 0x6e);

	/* Initiate calibration */
	/* TODO: use rt2800_rf_init_calibration ? */
	rfcsr = rt2800_rfcsr_read(rt2x00dev, 2);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_EN, 1);
	rt2800_rfcsr_write(rt2x00dev, 2, rfcsr);

	rt2800_freq_cal_mode1(rt2x00dev);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 18);
	rt2x00_set_field8(&rfcsr, RFCSR18_XO_TUNE_BYPASS, 1);
	rt2800_rfcsr_write(rt2x00dev, 18, rfcsr);

	reg = rt2800_register_read(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
	rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
	rt2800_register_write(rt2x00dev, LDO_CFG0, reg);
	usleep_range(1000, 1500);
	reg = rt2800_register_read(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 0);
	rt2800_register_write(rt2x00dev, LDO_CFG0, reg);

	/* Set initial values for RX filter calibration */
	drv_data->calibration_bw20 = 0x1f;
	drv_data->calibration_bw40 = 0x2f;

	/* Save BBP 25 & 26 values for later use in channel switching */
	drv_data->bbp25 = rt2800_bbp_read(rt2x00dev, 25);
	drv_data->bbp26 = rt2800_bbp_read(rt2x00dev, 26);

	rt2800_led_open_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3593(rt2x00dev);

	rt3593_post_bbp_init(rt2x00dev);

	/* TODO: enable stream mode support */
}