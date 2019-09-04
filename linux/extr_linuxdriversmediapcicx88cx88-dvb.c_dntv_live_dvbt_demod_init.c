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
typedef  int /*<<< orphan*/  reset ;
typedef  int /*<<< orphan*/  dntv_extra ;
typedef  int /*<<< orphan*/  clock_config ;
typedef  int /*<<< orphan*/  capt_range_cfg ;
typedef  int /*<<< orphan*/  agc_cfg ;
typedef  int /*<<< orphan*/  adc_ctl_1_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  mt352_write (struct dvb_frontend*,int const*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dntv_live_dvbt_demod_init(struct dvb_frontend *fe)
{
	static const u8 clock_config[]  = { 0x89, 0x38, 0x39 };
	static const u8 reset[]         = { 0x50, 0x80 };
	static const u8 adc_ctl_1_cfg[] = { 0x8E, 0x40 };
	static const u8 agc_cfg[]       = { 0x67, 0x10, 0x23, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 };
	static const u8 dntv_extra[]     = { 0xB5, 0x7A };
	static const u8 capt_range_cfg[] = { 0x75, 0x32 };

	mt352_write(fe, clock_config,   sizeof(clock_config));
	udelay(2000);
	mt352_write(fe, reset,          sizeof(reset));
	mt352_write(fe, adc_ctl_1_cfg,  sizeof(adc_ctl_1_cfg));

	mt352_write(fe, agc_cfg,        sizeof(agc_cfg));
	udelay(2000);
	mt352_write(fe, dntv_extra,     sizeof(dntv_extra));
	mt352_write(fe, capt_range_cfg, sizeof(capt_range_cfg));

	return 0;
}