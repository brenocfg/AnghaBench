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
struct bnx2x {int dummy; } ;

/* Variables and functions */
#define  BNX2X_CHIP_MASK_ALL 170 
 int BNX2X_CHIP_MASK_E1 ; 
 int BNX2X_CHIP_MASK_E1H ; 
#define  BNX2X_CHIP_MASK_E1X 169 
#define  BNX2X_CHIP_MASK_E2 168 
#define  BNX2X_CHIP_MASK_E3 167 
#define  BNX2X_CHIP_MASK_E3B0 166 
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int BP_PORT (struct bnx2x*) ; 
#define  BRB1_REG_PAUSE_LOW_THRESHOLD_0 165 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3B0 (struct bnx2x*) ; 
#define  DORQ_REG_DB_ADDR0 164 
 int /*<<< orphan*/  DP (int,char*,...) ; 
 int ENODEV ; 
#define  HC_REG_AGG_INT_0 163 
#define  NIG_REG_BMAC0_IN_EN 162 
#define  NIG_REG_BRB0_OUT_EN 161 
#define  NIG_REG_EMAC0_IN_EN 160 
#define  NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 159 
#define  NIG_REG_LLH0_ACPI_PAT_0_CRC 158 
#define  NIG_REG_LLH0_ACPI_PAT_6_LEN 157 
#define  NIG_REG_LLH0_DEST_IP_0_1 156 
#define  NIG_REG_LLH0_DEST_MAC_0_0 155 
#define  NIG_REG_LLH0_DEST_TCP_0 154 
#define  NIG_REG_LLH0_DEST_UDP_0 153 
#define  NIG_REG_LLH0_IPV4_IPV6_0 152 
#define  NIG_REG_LLH0_T_BIT 151 
#define  NIG_REG_LLH0_VLAN_ID_0 150 
#define  NIG_REG_LLH0_XCM_MASK 149 
#define  NIG_REG_SERDES0_CTRL_PHY_ADDR 148 
#define  NIG_REG_STATUS_INTERRUPT_PORT0 147 
#define  NIG_REG_XCM0_OUT_EN 146 
#define  NIG_REG_XGXS0_CTRL_EXTREMOTEMDIOST 145 
#define  NIG_REG_XGXS_SERDES0_MODE_SEL 144 
#define  PBF_REG_INIT_CRD_Q0 143 
#define  PBF_REG_MAC_IF0_ENABLE 142 
#define  PBF_REG_P0_INIT_CRD 141 
#define  PRS_REG_CID_PORT_0 140 
#define  PXP2_REG_PSWRQ_CDU0_L2P 139 
#define  PXP2_REG_PSWRQ_TM0_L2P 138 
#define  PXP2_REG_PSWRQ_TSDM0_L2P 137 
#define  PXP2_REG_RQ_CDU0_EFIRST_MEM_ADDR 136 
#define  PXP2_REG_RQ_USDM0_EFIRST_MEM_ADDR 135 
#define  QM_REG_CONNNUM_0 134 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
#define  SRC_REG_KEYRSS0_0 133 
#define  SRC_REG_KEYRSS0_7 132 
#define  TM_REG_LIN0_MAX_ACTIVE_CID 131 
#define  XCM_REG_GLB_DEL_ACK_MAX_CNT_0 130 
#define  XCM_REG_WU_DA_CNT_CMD00 129 
#define  XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD00 128 
 int /*<<< orphan*/  bnx2x_is_nvm_accessible (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_test_registers(struct bnx2x *bp)
{
	int idx, i, rc = -ENODEV;
	u32 wr_val = 0, hw;
	int port = BP_PORT(bp);
	static const struct {
		u32 hw;
		u32 offset0;
		u32 offset1;
		u32 mask;
	} reg_tbl[] = {
/* 0 */		{ BNX2X_CHIP_MASK_ALL,
			BRB1_REG_PAUSE_LOW_THRESHOLD_0,	4, 0x000003ff },
		{ BNX2X_CHIP_MASK_ALL,
			DORQ_REG_DB_ADDR0,		4, 0xffffffff },
		{ BNX2X_CHIP_MASK_E1X,
			HC_REG_AGG_INT_0,		4, 0x000003ff },
		{ BNX2X_CHIP_MASK_ALL,
			PBF_REG_MAC_IF0_ENABLE,		4, 0x00000001 },
		{ BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2 | BNX2X_CHIP_MASK_E3,
			PBF_REG_P0_INIT_CRD,		4, 0x000007ff },
		{ BNX2X_CHIP_MASK_E3B0,
			PBF_REG_INIT_CRD_Q0,		4, 0x000007ff },
		{ BNX2X_CHIP_MASK_ALL,
			PRS_REG_CID_PORT_0,		4, 0x00ffffff },
		{ BNX2X_CHIP_MASK_ALL,
			PXP2_REG_PSWRQ_CDU0_L2P,	4, 0x000fffff },
		{ BNX2X_CHIP_MASK_ALL,
			PXP2_REG_RQ_CDU0_EFIRST_MEM_ADDR, 8, 0x0003ffff },
		{ BNX2X_CHIP_MASK_ALL,
			PXP2_REG_PSWRQ_TM0_L2P,		4, 0x000fffff },
/* 10 */	{ BNX2X_CHIP_MASK_ALL,
			PXP2_REG_RQ_USDM0_EFIRST_MEM_ADDR, 8, 0x0003ffff },
		{ BNX2X_CHIP_MASK_ALL,
			PXP2_REG_PSWRQ_TSDM0_L2P,	4, 0x000fffff },
		{ BNX2X_CHIP_MASK_ALL,
			QM_REG_CONNNUM_0,		4, 0x000fffff },
		{ BNX2X_CHIP_MASK_ALL,
			TM_REG_LIN0_MAX_ACTIVE_CID,	4, 0x0003ffff },
		{ BNX2X_CHIP_MASK_ALL,
			SRC_REG_KEYRSS0_0,		40, 0xffffffff },
		{ BNX2X_CHIP_MASK_ALL,
			SRC_REG_KEYRSS0_7,		40, 0xffffffff },
		{ BNX2X_CHIP_MASK_ALL,
			XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD00, 4, 0x00000001 },
		{ BNX2X_CHIP_MASK_ALL,
			XCM_REG_WU_DA_CNT_CMD00,	4, 0x00000003 },
		{ BNX2X_CHIP_MASK_ALL,
			XCM_REG_GLB_DEL_ACK_MAX_CNT_0,	4, 0x000000ff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_T_BIT,		4, 0x00000001 },
/* 20 */	{ BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_EMAC0_IN_EN,		4, 0x00000001 },
		{ BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_BMAC0_IN_EN,		4, 0x00000001 },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_XCM0_OUT_EN,		4, 0x00000001 },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_BRB0_OUT_EN,		4, 0x00000001 },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_XCM_MASK,		4, 0x00000007 },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_ACPI_PAT_6_LEN,	68, 0x000000ff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_ACPI_PAT_0_CRC,	68, 0xffffffff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_MAC_0_0,	160, 0xffffffff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_IP_0_1,	160, 0xffffffff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_IPV4_IPV6_0,	160, 0x00000001 },
/* 30 */	{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_UDP_0,	160, 0x0000ffff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_TCP_0,	160, 0x0000ffff },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_VLAN_ID_0,	160, 0x00000fff },
		{ BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_XGXS_SERDES0_MODE_SEL,	4, 0x00000001 },
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0, 4, 0x00000001},
		{ BNX2X_CHIP_MASK_ALL,
			NIG_REG_STATUS_INTERRUPT_PORT0,	4, 0x07ffffff },
		{ BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_XGXS0_CTRL_EXTREMOTEMDIOST, 24, 0x00000001 },
		{ BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_SERDES0_CTRL_PHY_ADDR,	16, 0x0000001f },

		{ BNX2X_CHIP_MASK_ALL, 0xffffffff, 0, 0x00000000 }
	};

	if (!bnx2x_is_nvm_accessible(bp)) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		return rc;
	}

	if (CHIP_IS_E1(bp))
		hw = BNX2X_CHIP_MASK_E1;
	else if (CHIP_IS_E1H(bp))
		hw = BNX2X_CHIP_MASK_E1H;
	else if (CHIP_IS_E2(bp))
		hw = BNX2X_CHIP_MASK_E2;
	else if (CHIP_IS_E3B0(bp))
		hw = BNX2X_CHIP_MASK_E3B0;
	else /* e3 A0 */
		hw = BNX2X_CHIP_MASK_E3;

	/* Repeat the test twice:
	 * First by writing 0x00000000, second by writing 0xffffffff
	 */
	for (idx = 0; idx < 2; idx++) {

		switch (idx) {
		case 0:
			wr_val = 0;
			break;
		case 1:
			wr_val = 0xffffffff;
			break;
		}

		for (i = 0; reg_tbl[i].offset0 != 0xffffffff; i++) {
			u32 offset, mask, save_val, val;
			if (!(hw & reg_tbl[i].hw))
				continue;

			offset = reg_tbl[i].offset0 + port*reg_tbl[i].offset1;
			mask = reg_tbl[i].mask;

			save_val = REG_RD(bp, offset);

			REG_WR(bp, offset, wr_val & mask);

			val = REG_RD(bp, offset);

			/* Restore the original register's value */
			REG_WR(bp, offset, save_val);

			/* verify value is as expected */
			if ((val & mask) != (wr_val & mask)) {
				DP(BNX2X_MSG_ETHTOOL,
				   "offset 0x%x: val 0x%x != 0x%x mask 0x%x\n",
				   offset, val, wr_val, mask);
				goto test_reg_exit;
			}
		}
	}

	rc = 0;

test_reg_exit:
	return rc;
}