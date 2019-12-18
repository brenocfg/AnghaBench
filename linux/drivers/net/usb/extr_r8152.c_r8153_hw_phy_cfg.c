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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8152 {int version; int /*<<< orphan*/  flags; scalar_t__ eee_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTAP_SHORT_EN ; 
 int /*<<< orphan*/  EEE_CLKDIV_EN ; 
 int /*<<< orphan*/  EN_10M_BGOFF ; 
 int /*<<< orphan*/  EN_10M_PLLOFF ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  OCP_DOWN_SPEED ; 
 int /*<<< orphan*/  OCP_EEE_CFG ; 
 int /*<<< orphan*/  OCP_POWER_CFG ; 
 int /*<<< orphan*/  PFM_PWM_SWITCH ; 
 int /*<<< orphan*/  PHY_RESET ; 
 int /*<<< orphan*/  PLA_PHY_PWR ; 
#define  RTL_VER_03 131 
#define  RTL_VER_04 130 
#define  RTL_VER_05 129 
#define  RTL_VER_06 128 
 int /*<<< orphan*/  SRAM_10M_AMP1 ; 
 int /*<<< orphan*/  SRAM_10M_AMP2 ; 
 int /*<<< orphan*/  SRAM_IMPEDANCE ; 
 int /*<<< orphan*/  SRAM_LPF_CFG ; 
 int /*<<< orphan*/  ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_reg_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_reg_write (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152b_enable_fc (struct r8152*) ; 
 int /*<<< orphan*/  r8153_aldps_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_eee_enable (struct r8152*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sram_write (struct r8152*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r8153_hw_phy_cfg(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	/* disable ALDPS before updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	rtl_eee_enable(tp, false);

	if (tp->version == RTL_VER_03) {
		data = ocp_reg_read(tp, OCP_EEE_CFG);
		data &= ~CTAP_SHORT_EN;
		ocp_reg_write(tp, OCP_EEE_CFG, data);
	}

	data = ocp_reg_read(tp, OCP_POWER_CFG);
	data |= EEE_CLKDIV_EN;
	ocp_reg_write(tp, OCP_POWER_CFG, data);

	data = ocp_reg_read(tp, OCP_DOWN_SPEED);
	data |= EN_10M_BGOFF;
	ocp_reg_write(tp, OCP_DOWN_SPEED, data);
	data = ocp_reg_read(tp, OCP_POWER_CFG);
	data |= EN_10M_PLLOFF;
	ocp_reg_write(tp, OCP_POWER_CFG, data);
	sram_write(tp, SRAM_IMPEDANCE, 0x0b13);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	/* Enable LPF corner auto tune */
	sram_write(tp, SRAM_LPF_CFG, 0xf70f);

	/* Adjust 10M Amplitude */
	sram_write(tp, SRAM_10M_AMP1, 0x00af);
	sram_write(tp, SRAM_10M_AMP2, 0x0208);

	if (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
		break;
	case RTL_VER_05:
	case RTL_VER_06:
	default:
		r8153_u2p3en(tp, true);
		break;
	}

	set_bit(PHY_RESET, &tp->flags);
}