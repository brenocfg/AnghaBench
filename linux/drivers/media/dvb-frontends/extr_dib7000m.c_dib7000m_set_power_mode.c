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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  mobile_mode; } ;
struct dib7000m_state {int revision; TYPE_1__ cfg; } ;
typedef  enum dib7000m_power_mode { ____Placeholder_dib7000m_power_mode } dib7000m_power_mode ;

/* Variables and functions */
#define  DIB7000M_POWER_ALL 133 
#define  DIB7000M_POWER_COR4_CRY_ESRAM_MOUT_NUD 132 
#define  DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD 131 
#define  DIB7000M_POWER_INTERFACE_ONLY 130 
#define  DIB7000M_POWER_INTERF_ANALOG_AGC 129 
#define  DIB7000M_POWER_NO 128 
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,int,int) ; 

__attribute__((used)) static void dib7000m_set_power_mode(struct dib7000m_state *state, enum dib7000m_power_mode mode)
{
	/* by default everything is going to be powered off */
	u16 reg_903 = 0xffff, reg_904 = 0xffff, reg_905 = 0xffff, reg_906  = 0x3fff;
	u8  offset = 0;

	/* now, depending on the requested mode, we power on */
	switch (mode) {
		/* power up everything in the demod */
		case DIB7000M_POWER_ALL:
			reg_903 = 0x0000; reg_904 = 0x0000; reg_905 = 0x0000; reg_906 = 0x0000;
			break;

		/* just leave power on the control-interfaces: GPIO and (I2C or SDIO or SRAM) */
		case DIB7000M_POWER_INTERFACE_ONLY: /* TODO power up either SDIO or I2C or SRAM */
			reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 2));
			break;

		case DIB7000M_POWER_INTERF_ANALOG_AGC:
			reg_903 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10));
			reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 2));
			reg_906 &= ~((1 << 0));
			break;

		case DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD:
			reg_903 = 0x0000; reg_904 = 0x801f; reg_905 = 0x0000; reg_906 = 0x0000;
			break;

		case DIB7000M_POWER_COR4_CRY_ESRAM_MOUT_NUD:
			reg_903 = 0x0000; reg_904 = 0x8000; reg_905 = 0x010b; reg_906 = 0x0000;
			break;
		case DIB7000M_POWER_NO:
			break;
	}

	/* always power down unused parts */
	if (!state->cfg.mobile_mode)
		reg_904 |= (1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 1);

	/* P_sdio_select_clk = 0 on MC and after*/
	if (state->revision != 0x4000)
		reg_906 <<= 1;

	if (state->revision == 0x4003)
		offset = 1;

	dib7000m_write_word(state, 903 + offset, reg_903);
	dib7000m_write_word(state, 904 + offset, reg_904);
	dib7000m_write_word(state, 905 + offset, reg_905);
	dib7000m_write_word(state, 906 + offset, reg_906);
}