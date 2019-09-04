#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  mobile_mode; } ;
struct TYPE_4__ {TYPE_1__ host; } ;
struct dib9000_state {int revision; TYPE_2__ platform; } ;
typedef  enum dib9000_power_mode { ____Placeholder_dib9000_power_mode } dib9000_power_mode ;

/* Variables and functions */
#define  DIB9000_POWER_ALL 133 
#define  DIB9000_POWER_COR4_CRY_ESRAM_MOUT_NUD 132 
#define  DIB9000_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD 131 
#define  DIB9000_POWER_INTERFACE_ONLY 130 
#define  DIB9000_POWER_INTERF_ANALOG_AGC 129 
#define  DIB9000_POWER_NO 128 
 int dib9000_read_word (struct dib9000_state*,int) ; 
 int /*<<< orphan*/  dib9000_write_word (struct dib9000_state*,int,int) ; 

__attribute__((used)) static void dib9000_set_power_mode(struct dib9000_state *state, enum dib9000_power_mode mode)
{
	/* by default everything is going to be powered off */
	u16 reg_903 = 0x3fff, reg_904 = 0xffff, reg_905 = 0xffff, reg_906;
	u8 offset;

	if (state->revision == 0x4003 || state->revision == 0x4004 || state->revision == 0x4005)
		offset = 1;
	else
		offset = 0;

	reg_906 = dib9000_read_word(state, 906 + offset) | 0x3;	/* keep settings for RISC */

	/* now, depending on the requested mode, we power on */
	switch (mode) {
		/* power up everything in the demod */
	case DIB9000_POWER_ALL:
		reg_903 = 0x0000;
		reg_904 = 0x0000;
		reg_905 = 0x0000;
		reg_906 = 0x0000;
		break;

		/* just leave power on the control-interfaces: GPIO and (I2C or SDIO or SRAM) */
	case DIB9000_POWER_INTERFACE_ONLY:	/* TODO power up either SDIO or I2C or SRAM */
		reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 2));
		break;

	case DIB9000_POWER_INTERF_ANALOG_AGC:
		reg_903 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10));
		reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 2));
		reg_906 &= ~((1 << 0));
		break;

	case DIB9000_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD:
		reg_903 = 0x0000;
		reg_904 = 0x801f;
		reg_905 = 0x0000;
		reg_906 &= ~((1 << 0));
		break;

	case DIB9000_POWER_COR4_CRY_ESRAM_MOUT_NUD:
		reg_903 = 0x0000;
		reg_904 = 0x8000;
		reg_905 = 0x010b;
		reg_906 &= ~((1 << 0));
		break;
	default:
	case DIB9000_POWER_NO:
		break;
	}

	/* always power down unused parts */
	if (!state->platform.host.mobile_mode)
		reg_904 |= (1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 1);

	/* P_sdio_select_clk = 0 on MC and after */
	if (state->revision != 0x4000)
		reg_906 <<= 1;

	dib9000_write_word(state, 903 + offset, reg_903);
	dib9000_write_word(state, 904 + offset, reg_904);
	dib9000_write_word(state, 905 + offset, reg_905);
	dib9000_write_word(state, 906 + offset, reg_906);
}