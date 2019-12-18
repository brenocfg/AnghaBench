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
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  mt352_sec_agc_cfg5 ;
typedef  int /*<<< orphan*/  mt352_sec_agc_cfg4 ;
typedef  int /*<<< orphan*/  mt352_sec_agc_cfg3 ;
typedef  int /*<<< orphan*/  mt352_sec_agc_cfg2 ;
typedef  int /*<<< orphan*/  mt352_sec_agc_cfg1 ;
typedef  int /*<<< orphan*/  mt352_reset ;
typedef  int /*<<< orphan*/  mt352_mclk_ratio ;
typedef  int /*<<< orphan*/  mt352_input_freq_1 ;
typedef  int /*<<< orphan*/  mt352_clock_config ;
typedef  int /*<<< orphan*/  mt352_agc_cfg ;
typedef  int /*<<< orphan*/  mt352_adc_ctl_1_cfg ;
typedef  int /*<<< orphan*/  mt352_acq_ctl ;

/* Variables and functions */
 int /*<<< orphan*/  mt352_write (struct dvb_frontend*,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int umt_mt352_demod_init(struct dvb_frontend *fe)
{
	static u8 mt352_clock_config[] = { 0x89, 0xb8, 0x2d };
	static u8 mt352_reset[] = { 0x50, 0x80 };
	static u8 mt352_mclk_ratio[] = { 0x8b, 0x00 };
	static u8 mt352_adc_ctl_1_cfg[] = { 0x8E, 0x40 };
	static u8 mt352_agc_cfg[] = { 0x67, 0x10, 0xa0 };

	static u8 mt352_sec_agc_cfg1[] = { 0x6a, 0xff };
	static u8 mt352_sec_agc_cfg2[] = { 0x6d, 0xff };
	static u8 mt352_sec_agc_cfg3[] = { 0x70, 0x40 };
	static u8 mt352_sec_agc_cfg4[] = { 0x7b, 0x03 };
	static u8 mt352_sec_agc_cfg5[] = { 0x7d, 0x0f };

	static u8 mt352_acq_ctl[] = { 0x53, 0x50 };
	static u8 mt352_input_freq_1[] = { 0x56, 0x31, 0x06 };

	mt352_write(fe, mt352_clock_config, sizeof(mt352_clock_config));
	udelay(2000);
	mt352_write(fe, mt352_reset, sizeof(mt352_reset));
	mt352_write(fe, mt352_mclk_ratio, sizeof(mt352_mclk_ratio));

	mt352_write(fe, mt352_adc_ctl_1_cfg, sizeof(mt352_adc_ctl_1_cfg));
	mt352_write(fe, mt352_agc_cfg, sizeof(mt352_agc_cfg));

	mt352_write(fe, mt352_sec_agc_cfg1, sizeof(mt352_sec_agc_cfg1));
	mt352_write(fe, mt352_sec_agc_cfg2, sizeof(mt352_sec_agc_cfg2));
	mt352_write(fe, mt352_sec_agc_cfg3, sizeof(mt352_sec_agc_cfg3));
	mt352_write(fe, mt352_sec_agc_cfg4, sizeof(mt352_sec_agc_cfg4));
	mt352_write(fe, mt352_sec_agc_cfg5, sizeof(mt352_sec_agc_cfg5));

	mt352_write(fe, mt352_acq_ctl, sizeof(mt352_acq_ctl));
	mt352_write(fe, mt352_input_freq_1, sizeof(mt352_input_freq_1));

	return 0;
}