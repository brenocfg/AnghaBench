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
typedef  int u32 ;
struct odm_dm_struct {int* mp_mode; int /*<<< orphan*/  AntDivType; struct adapter* Adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CGCS_RX_SW_ANTDIV ; 
 int /*<<< orphan*/  MAIN_ANT ; 
 int /*<<< orphan*/  ODM_REG_ANTDIV_PARA1_11N ; 
 int /*<<< orphan*/  ODM_REG_ANTSEL_PIN_11N ; 
 int /*<<< orphan*/  ODM_REG_ANT_MAPPING1_11N ; 
 int /*<<< orphan*/  ODM_REG_BB_PWR_SAV4_11N ; 
 int /*<<< orphan*/  ODM_REG_CCK_ANTDIV_PARA2_11N ; 
 int /*<<< orphan*/  ODM_REG_IGI_A_11N ; 
 int /*<<< orphan*/  ODM_REG_LNA_SWITCH_11N ; 
 int /*<<< orphan*/  ODM_REG_PIN_CTRL_11N ; 
 int /*<<< orphan*/  ODM_REG_RX_ANT_CTRL_11N ; 
 int bMaskDWord ; 
 int phy_query_bb_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl88eu_dm_update_rx_idle_ant (struct odm_dm_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_rx_hw_antena_div_init(struct odm_dm_struct *dm_odm)
{
	struct adapter *adapter = dm_odm->Adapter;
	u32 value32;

	if (*dm_odm->mp_mode == 1) {
		dm_odm->AntDivType = CGCS_RX_SW_ANTDIV;
		phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 0);
		phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(31), 1);
		return;
	}

	/* MAC Setting */
	value32 = phy_query_bb_reg(adapter, ODM_REG_ANTSEL_PIN_11N, bMaskDWord);
	phy_set_bb_reg(adapter, ODM_REG_ANTSEL_PIN_11N, bMaskDWord,
		       value32 | (BIT(23) | BIT(25)));
	/* Pin Settings */
	phy_set_bb_reg(adapter, ODM_REG_PIN_CTRL_11N, BIT(9) | BIT(8), 0);
	phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N, BIT(10), 0);
	phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(22), 1);
	phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(31), 1);
	/* OFDM Settings */
	phy_set_bb_reg(adapter, ODM_REG_ANTDIV_PARA1_11N, bMaskDWord,
		       0x000000a0);
	/* CCK Settings */
	phy_set_bb_reg(adapter, ODM_REG_BB_PWR_SAV4_11N, BIT(7), 1);
	phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA2_11N, BIT(4), 1);
	rtl88eu_dm_update_rx_idle_ant(dm_odm, MAIN_ANT);
	phy_set_bb_reg(adapter, ODM_REG_ANT_MAPPING1_11N, 0xFFFF, 0x0201);
}