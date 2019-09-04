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
typedef  int u16 ;
struct dib7000p_state {scalar_t__ version; } ;
typedef  enum dib7000p_power_mode { ____Placeholder_dib7000p_power_mode } dib7000p_power_mode ;

/* Variables and functions */
#define  DIB7000P_POWER_ALL 130 
#define  DIB7000P_POWER_ANALOG_ADC 129 
#define  DIB7000P_POWER_INTERFACE_ONLY 128 
 scalar_t__ SOC7090 ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 

__attribute__((used)) static int dib7000p_set_power_mode(struct dib7000p_state *state, enum dib7000p_power_mode mode)
{
	/* by default everything is powered off */
	u16 reg_774 = 0x3fff, reg_775 = 0xffff, reg_776 = 0x0007, reg_899 = 0x0003, reg_1280 = (0xfe00) | (dib7000p_read_word(state, 1280) & 0x01ff);

	/* now, depending on the requested mode, we power on */
	switch (mode) {
		/* power up everything in the demod */
	case DIB7000P_POWER_ALL:
		reg_774 = 0x0000;
		reg_775 = 0x0000;
		reg_776 = 0x0;
		reg_899 = 0x0;
		if (state->version == SOC7090)
			reg_1280 &= 0x001f;
		else
			reg_1280 &= 0x01ff;
		break;

	case DIB7000P_POWER_ANALOG_ADC:
		/* dem, cfg, iqc, sad, agc */
		reg_774 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10) | (1 << 9));
		/* nud */
		reg_776 &= ~((1 << 0));
		/* Dout */
		if (state->version != SOC7090)
			reg_1280 &= ~((1 << 11));
		reg_1280 &= ~(1 << 6);
		/* fall-through */
	case DIB7000P_POWER_INTERFACE_ONLY:
		/* just leave power on the control-interfaces: GPIO and (I2C or SDIO) */
		/* TODO power up either SDIO or I2C */
		if (state->version == SOC7090)
			reg_1280 &= ~((1 << 7) | (1 << 5));
		else
			reg_1280 &= ~((1 << 14) | (1 << 13) | (1 << 12) | (1 << 10));
		break;

/* TODO following stuff is just converted from the dib7000-driver - check when is used what */
	}

	dib7000p_write_word(state, 774, reg_774);
	dib7000p_write_word(state, 775, reg_775);
	dib7000p_write_word(state, 776, reg_776);
	dib7000p_write_word(state, 1280, reg_1280);
	if (state->version != SOC7090)
		dib7000p_write_word(state, 899, reg_899);

	return 0;
}