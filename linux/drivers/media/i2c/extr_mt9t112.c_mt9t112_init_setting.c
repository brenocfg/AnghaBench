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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAR (int,int) ; 
 int /*<<< orphan*/  VAR8 (int,int) ; 
 int /*<<< orphan*/  mt9t112_mcu_mask_set (int,struct i2c_client const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt9t112_mcu_write (int,struct i2c_client const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9t112_init_setting(const struct i2c_client *client)
{
	int ret;

	/* Adaptive Output Clock (A) */
	mt9t112_mcu_mask_set(ret, client, VAR(26, 160), 0x0040, 0x0000);

	/* Read Mode (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 12), 0x0024);

	/* Fine Correction (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 15), 0x00CC);

	/* Fine IT Min (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 17), 0x01f1);

	/* Fine IT Max Margin (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 19), 0x00fF);

	/* Base Frame Lines (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 29), 0x032D);

	/* Min Line Length (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 31), 0x073a);

	/* Line Length (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 37), 0x07d0);

	/* Adaptive Output Clock (B) */
	mt9t112_mcu_mask_set(ret, client, VAR(27, 160), 0x0040, 0x0000);

	/* Row Start (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 74), 0x004);

	/* Column Start (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 76), 0x004);

	/* Row End (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 78), 0x60B);

	/* Column End (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 80), 0x80B);

	/* Fine Correction (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 87), 0x008C);

	/* Fine IT Min (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 89), 0x01F1);

	/* Fine IT Max Margin (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 91), 0x00FF);

	/* Base Frame Lines (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 101), 0x0668);

	/* Min Line Length (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 103), 0x0AF0);

	/* Line Length (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 109), 0x0AF0);

	/*
	 * Flicker Detection registers.
	 * This section should be replaced whenever new timing file is
	 * generated. All the following registers need to be replaced.
	 * Following registers are generated from Register Wizard but user can
	 * modify them. For detail see auto flicker detection tuning.
	 */

	/* FD_FDPERIOD_SELECT */
	mt9t112_mcu_write(ret, client, VAR8(8, 5), 0x01);

	/* PRI_B_CONFIG_FD_ALGO_RUN */
	mt9t112_mcu_write(ret, client, VAR(27, 17), 0x0003);

	/* PRI_A_CONFIG_FD_ALGO_RUN */
	mt9t112_mcu_write(ret, client, VAR(26, 17), 0x0003);

	/*
	 * AFD range detection tuning registers.
	 */

	/* Search_f1_50 */
	mt9t112_mcu_write(ret, client, VAR8(18, 165), 0x25);

	/* Search_f2_50 */
	mt9t112_mcu_write(ret, client, VAR8(18, 166), 0x28);

	/* Search_f1_60 */
	mt9t112_mcu_write(ret, client, VAR8(18, 167), 0x2C);

	/* Search_f2_60 */
	mt9t112_mcu_write(ret, client, VAR8(18, 168), 0x2F);

	/* Period_50Hz (A) */
	mt9t112_mcu_write(ret, client, VAR8(18, 68), 0xBA);

	/* Secret register by Aptina. */
	/* Period_50Hz (A MSB) */
	mt9t112_mcu_write(ret, client, VAR8(18, 303), 0x00);

	/* Period_60Hz (A) */
	mt9t112_mcu_write(ret, client, VAR8(18, 69), 0x9B);

	/* Secret register by Aptina. */
	/* Period_60Hz (A MSB) */
	mt9t112_mcu_write(ret, client, VAR8(18, 301), 0x00);

	/* Period_50Hz (B) */
	mt9t112_mcu_write(ret, client, VAR8(18, 140), 0x82);

	/* Secret register by Aptina. */
	/* Period_50Hz (B) MSB */
	mt9t112_mcu_write(ret, client, VAR8(18, 304), 0x00);

	/* Period_60Hz (B) */
	mt9t112_mcu_write(ret, client, VAR8(18, 141), 0x6D);

	/* Secret register by Aptina. */
	/* Period_60Hz (B) MSB */
	mt9t112_mcu_write(ret, client, VAR8(18, 302), 0x00);

	/* FD Mode */
	mt9t112_mcu_write(ret, client, VAR8(8, 2), 0x10);

	/* Stat_min */
	mt9t112_mcu_write(ret, client, VAR8(8, 9), 0x02);

	/* Stat_max */
	mt9t112_mcu_write(ret, client, VAR8(8, 10), 0x03);

	/* Min_amplitude */
	mt9t112_mcu_write(ret, client, VAR8(8, 12), 0x0A);

	/* RX FIFO Watermark (A) */
	mt9t112_mcu_write(ret, client, VAR(18, 70), 0x0014);

	/* RX FIFO Watermark (B) */
	mt9t112_mcu_write(ret, client, VAR(18, 142), 0x0014);

	/* MCLK: 16MHz
	 * PCLK: 73MHz
	 * CorePixCLK: 36.5 MHz
	 */
	mt9t112_mcu_write(ret, client, VAR8(18, 0x0044), 133);
	mt9t112_mcu_write(ret, client, VAR8(18, 0x0045), 110);
	mt9t112_mcu_write(ret, client, VAR8(18, 0x008c), 130);
	mt9t112_mcu_write(ret, client, VAR8(18, 0x008d), 108);

	mt9t112_mcu_write(ret, client, VAR8(18, 0x00A5), 27);
	mt9t112_mcu_write(ret, client, VAR8(18, 0x00a6), 30);
	mt9t112_mcu_write(ret, client, VAR8(18, 0x00a7), 32);
	mt9t112_mcu_write(ret, client, VAR8(18, 0x00a8), 35);

	return ret;
}