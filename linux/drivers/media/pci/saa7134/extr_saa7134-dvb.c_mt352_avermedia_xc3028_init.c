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
typedef  int /*<<< orphan*/  clock_config ;
typedef  int /*<<< orphan*/  capt_range_cfg ;
typedef  int /*<<< orphan*/  agc_cfg ;
typedef  int /*<<< orphan*/  adc_ctl_1_cfg ;

/* Variables and functions */
#define  ADC_CTL_1 132 
#define  AGC_TARGET 131 
#define  CAPT_RANGE 130 
#define  CLOCK_CTL 129 
#define  RESET 128 
 int /*<<< orphan*/  mt352_write (struct dvb_frontend*,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt352_avermedia_xc3028_init(struct dvb_frontend *fe)
{
	static u8 clock_config []  = { CLOCK_CTL, 0x38, 0x2d };
	static u8 reset []         = { RESET, 0x80 };
	static u8 adc_ctl_1_cfg [] = { ADC_CTL_1, 0x40 };
	static u8 agc_cfg []       = { AGC_TARGET, 0xe };
	static u8 capt_range_cfg[] = { CAPT_RANGE, 0x33 };

	mt352_write(fe, clock_config,   sizeof(clock_config));
	udelay(200);
	mt352_write(fe, reset,          sizeof(reset));
	mt352_write(fe, adc_ctl_1_cfg,  sizeof(adc_ctl_1_cfg));
	mt352_write(fe, agc_cfg,        sizeof(agc_cfg));
	mt352_write(fe, capt_range_cfg, sizeof(capt_range_cfg));
	return 0;
}