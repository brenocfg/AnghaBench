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

/* Variables and functions */
 int ADC_CTL_1 ; 
 int AGC_TARGET ; 
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int CLOCK_CTL ; 
 int CONFIG ; 
 int RESET ; 
 int /*<<< orphan*/  deb (char*) ; 
 int mt352_write (struct dvb_frontend*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m920x_mt352_demod_init(struct dvb_frontend *fe)
{
	int ret;
	u8 config[] = { CONFIG, 0x3d };
	u8 clock[] = { CLOCK_CTL, 0x30 };
	u8 reset[] = { RESET, 0x80 };
	u8 adc_ctl[] = { ADC_CTL_1, 0x40 };
	u8 agc[] = { AGC_TARGET, 0x1c, 0x20 };
	u8 sec_agc[] = { 0x69, 0x00, 0xff, 0xff, 0x40, 0xff, 0x00, 0x40, 0x40 };
	u8 unk1[] = { 0x93, 0x1a };
	u8 unk2[] = { 0xb5, 0x7a };

	deb("Demod init!\n");

	if ((ret = mt352_write(fe, config, ARRAY_SIZE(config))) != 0)
		return ret;
	if ((ret = mt352_write(fe, clock, ARRAY_SIZE(clock))) != 0)
		return ret;
	if ((ret = mt352_write(fe, reset, ARRAY_SIZE(reset))) != 0)
		return ret;
	if ((ret = mt352_write(fe, adc_ctl, ARRAY_SIZE(adc_ctl))) != 0)
		return ret;
	if ((ret = mt352_write(fe, agc, ARRAY_SIZE(agc))) != 0)
		return ret;
	if ((ret = mt352_write(fe, sec_agc, ARRAY_SIZE(sec_agc))) != 0)
		return ret;
	if ((ret = mt352_write(fe, unk1, ARRAY_SIZE(unk1))) != 0)
		return ret;
	if ((ret = mt352_write(fe, unk2, ARRAY_SIZE(unk2))) != 0)
		return ret;

	return 0;
}