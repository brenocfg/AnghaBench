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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCSR1_RF_BLOCK_EN ; 
 int /*<<< orphan*/  RFCSR2_RESCAL_BP ; 
 int /*<<< orphan*/  RFCSR2_RESCAL_EN ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_3883(struct rt2x00_dev *rt2x00dev)
{
	u8 rfcsr;

	/* TODO: get the actual ECO value from the SoC */
	const unsigned int eco = 5;

	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_write(rt2x00dev, 0, 0xe0);
	rt2800_rfcsr_write(rt2x00dev, 1, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 2, 0x50);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 8, 0x5b);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x08);
	rt2800_rfcsr_write(rt2x00dev, 10, 0xd3);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x48);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x1a);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x12);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x00);

	/* RFCSR 17 will be initialized later based on the
	 * frequency offset stored in the EEPROM
	 */

	rt2800_rfcsr_write(rt2x00dev, 18, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 21, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 23, 0xc0);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 34, 0x20);
	rt2800_rfcsr_write(rt2x00dev, 35, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 37, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 38, 0x86);
	rt2800_rfcsr_write(rt2x00dev, 39, 0x23);
	rt2800_rfcsr_write(rt2x00dev, 40, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 41, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 42, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 43, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 44, 0x93);
	rt2800_rfcsr_write(rt2x00dev, 45, 0xbb);
	rt2800_rfcsr_write(rt2x00dev, 46, 0x60);
	rt2800_rfcsr_write(rt2x00dev, 47, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 48, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 49, 0x8e);
	rt2800_rfcsr_write(rt2x00dev, 50, 0x86);
	rt2800_rfcsr_write(rt2x00dev, 51, 0x51);
	rt2800_rfcsr_write(rt2x00dev, 52, 0x05);
	rt2800_rfcsr_write(rt2x00dev, 53, 0x76);
	rt2800_rfcsr_write(rt2x00dev, 54, 0x76);
	rt2800_rfcsr_write(rt2x00dev, 55, 0x76);
	rt2800_rfcsr_write(rt2x00dev, 56, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 57, 0x3e);
	rt2800_rfcsr_write(rt2x00dev, 58, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 59, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 60, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 61, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 63, 0x00);

	/* TODO: rx filter calibration? */

	rt2800_bbp_write(rt2x00dev, 137, 0x0f);

	rt2800_bbp_write(rt2x00dev, 163, 0x9d);

	rt2800_bbp_write(rt2x00dev, 105, 0x05);

	rt2800_bbp_write(rt2x00dev, 179, 0x02);
	rt2800_bbp_write(rt2x00dev, 180, 0x00);
	rt2800_bbp_write(rt2x00dev, 182, 0x40);
	rt2800_bbp_write(rt2x00dev, 180, 0x01);
	rt2800_bbp_write(rt2x00dev, 182, 0x9c);

	rt2800_bbp_write(rt2x00dev, 179, 0x00);

	rt2800_bbp_write(rt2x00dev, 142, 0x04);
	rt2800_bbp_write(rt2x00dev, 143, 0x3b);
	rt2800_bbp_write(rt2x00dev, 142, 0x06);
	rt2800_bbp_write(rt2x00dev, 143, 0xa0);
	rt2800_bbp_write(rt2x00dev, 142, 0x07);
	rt2800_bbp_write(rt2x00dev, 143, 0xa1);
	rt2800_bbp_write(rt2x00dev, 142, 0x08);
	rt2800_bbp_write(rt2x00dev, 143, 0xa2);
	rt2800_bbp_write(rt2x00dev, 148, 0xc8);

	if (eco == 5) {
		rt2800_rfcsr_write(rt2x00dev, 32, 0xd8);
		rt2800_rfcsr_write(rt2x00dev, 33, 0x32);
	}

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 2);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_BP, 0);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_EN, 1);
	rt2800_rfcsr_write(rt2x00dev, 2, rfcsr);
	msleep(1);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_EN, 0);
	rt2800_rfcsr_write(rt2x00dev, 2, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2800_rfcsr_write(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 6);
	rfcsr |= 0xc0;
	rt2800_rfcsr_write(rt2x00dev, 6, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 22);
	rfcsr |= 0x20;
	rt2800_rfcsr_write(rt2x00dev, 22, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 46);
	rfcsr |= 0x20;
	rt2800_rfcsr_write(rt2x00dev, 46, rfcsr);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 20);
	rfcsr &= ~0xee;
	rt2800_rfcsr_write(rt2x00dev, 20, rfcsr);
}