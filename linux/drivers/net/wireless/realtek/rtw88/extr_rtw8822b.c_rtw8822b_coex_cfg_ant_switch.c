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
struct rtw_coex_rfe {int ant_switch_polarity; int rfe_module_type; scalar_t__ ant_switch_diversity; } ;
struct rtw_coex_dm {int cur_switch_status; } ;
struct rtw_coex {struct rtw_coex_rfe rfe; struct rtw_coex_dm dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int BIT_DPDT_SEL_EN ; 
 int BIT_DPDT_WL_SEL ; 
 int BIT_MASK_RFE_INV89 ; 
 int BIT_MASK_RFE_SEL89 ; 
 int BIT_SW_DPDT_SEL_DATA ; 
#define  COEX_SWITCH_CTRL_BY_ANTDIV 133 
#define  COEX_SWITCH_CTRL_BY_BBSW 132 
#define  COEX_SWITCH_CTRL_BY_BT 131 
#define  COEX_SWITCH_CTRL_BY_FW 130 
#define  COEX_SWITCH_CTRL_BY_MAC 129 
#define  COEX_SWITCH_CTRL_BY_PTA 128 
 int COEX_SWITCH_TO_WLG ; 
 int COEX_SWITCH_TO_WLG_BT ; 
 int /*<<< orphan*/  REG_LED_CFG ; 
 int /*<<< orphan*/  REG_PAD_CTRL1 ; 
 int /*<<< orphan*/  REG_RFE_CTRL8 ; 
 int /*<<< orphan*/  REG_RFE_INV8 ; 
 int /*<<< orphan*/  rtw_write8_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtw8822b_coex_cfg_ant_switch(struct rtw_dev *rtwdev,
					 u8 ctrl_type, u8 pos_type)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_coex_rfe *coex_rfe = &coex->rfe;
	bool polarity_inverse;
	u8 regval = 0;

	if (((ctrl_type << 8) + pos_type) == coex_dm->cur_switch_status)
		return;

	coex_dm->cur_switch_status = (ctrl_type << 8) + pos_type;

	if (coex_rfe->ant_switch_diversity &&
	    ctrl_type == COEX_SWITCH_CTRL_BY_BBSW)
		ctrl_type = COEX_SWITCH_CTRL_BY_ANTDIV;

	polarity_inverse = (coex_rfe->ant_switch_polarity == 1);

	switch (ctrl_type) {
	default:
	case COEX_SWITCH_CTRL_BY_BBSW:
		/* 0x4c[23] = 0 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		/* BB SW, DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
		rtw_write8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89, 0x77);

		if (pos_type == COEX_SWITCH_TO_WLG_BT) {
			if (coex_rfe->rfe_module_type != 0x4 &&
			    coex_rfe->rfe_module_type != 0x2)
				regval = 0x3;
			else
				regval = (!polarity_inverse ? 0x2 : 0x1);
		} else if (pos_type == COEX_SWITCH_TO_WLG) {
			regval = (!polarity_inverse ? 0x2 : 0x1);
		} else {
			regval = (!polarity_inverse ? 0x1 : 0x2);
		}

		rtw_write8_mask(rtwdev, REG_RFE_INV8, BIT_MASK_RFE_INV89, regval);
		break;
	case COEX_SWITCH_CTRL_BY_PTA:
		/* 0x4c[23] = 0 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		/* PTA,  DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
		rtw_write8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89, 0x66);

		regval = (!polarity_inverse ? 0x2 : 0x1);
		rtw_write8_mask(rtwdev, REG_RFE_INV8, BIT_MASK_RFE_INV89, regval);
		break;
	case COEX_SWITCH_CTRL_BY_ANTDIV:
		/* 0x4c[23] = 0 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		rtw_write8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89, 0x88);
		break;
	case COEX_SWITCH_CTRL_BY_MAC:
		/* 0x4c[23] = 1 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x1);

		regval = (!polarity_inverse ? 0x0 : 0x1);
		rtw_write8_mask(rtwdev, REG_PAD_CTRL1, BIT_SW_DPDT_SEL_DATA, regval);
		break;
	case COEX_SWITCH_CTRL_BY_FW:
		/* 0x4c[23] = 0 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		break;
	case COEX_SWITCH_CTRL_BY_BT:
		/* 0x4c[23] = 0 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 0 */
		rtw_write8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x0);
		break;
	}
}