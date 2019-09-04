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
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int DSAFV2_INODE_FINAL_IN_PAUSE_NUM_0_REG ; 
 int DSAF_ABNORMAL_TIMEOUT_0_REG ; 
 int DSAF_CFG_0_REG ; 
 int DSAF_COMM_CHN ; 
 int DSAF_DSA_REG_CNT_CLR_CE_REG ; 
 int DSAF_DSA_SBM_INF_FIFO_THRD_REG ; 
 int DSAF_DSA_SRAM_1BIT_ECC_CNT_REG ; 
 int DSAF_DSA_SRAM_1BIT_ECC_SEL_REG ; 
 int DSAF_ECC_ERR_INVERT_0_REG ; 
 int DSAF_FSM_TIMEOUT_0_REG ; 
 int DSAF_INODE_BD_ORDER_STATUS_0_REG ; 
 int DSAF_INODE_BD_SAVE_STATUS_0_REG ; 
 int DSAF_INODE_BP_DISCARD_NUM_0_REG ; 
 int DSAF_INODE_BP_STATUS_0_REG ; 
 int DSAF_INODE_CRC_FALSE_NUM_0_REG ; 
 int DSAF_INODE_CUT_THROUGH_CFG_0_REG ; 
 int DSAF_INODE_ECC_ERR_ADDR_0_REG ; 
 int DSAF_INODE_FIFO_WL_0_REG ; 
 int DSAF_INODE_FINAL_IN_MAN_NUM_0_REG ; 
 int DSAF_INODE_FINAL_IN_PAUSE_NUM_0_REG ; 
 int DSAF_INODE_FINAL_IN_PKT_NUM_0_REG ; 
 int DSAF_INODE_GE_FC_EN_0_REG ; 
 int DSAF_INODE_IN_DATA_STP_DISC_0_REG ; 
 int DSAF_INODE_IN_PORT_NUM_0_REG ; 
 int DSAF_INODE_LOCAL_ADDR_FALSE_NUM_0_REG ; 
 int DSAF_INODE_NUM ; 
 int DSAF_INODE_PAD_DISCARD_NUM_0_REG ; 
 int DSAF_INODE_PRI_TC_CFG_0_REG ; 
 int DSAF_INODE_RSLT_DISCARD_NUM_0_REG ; 
 int DSAF_INODE_SBM_DROP_NUM_0_REG ; 
 int DSAF_INODE_SBM_PID_NUM_0_REG ; 
 int DSAF_INODE_SBM_RELS_NUM_0_REG ; 
 int DSAF_INODE_SW_VLAN_TAG_DISC_0_REG ; 
 int DSAF_INODE_VC0_IN_PKT_NUM_0_REG ; 
 int DSAF_INODE_VC1_IN_PKT_NUM_0_REG ; 
 int DSAF_INODE_VOQ_OVER_NUM_0_REG ; 
 int DSAF_MIX_DEF_QID_0_REG ; 
 int DSAF_NETPORT_CTRL_SIG_0_REG ; 
 int DSAF_ONODE_FIFO_WL_0_REG ; 
 int DSAF_PAUSE_CFG_REG ; 
 int DSAF_PFC_EN_0_REG ; 
 int DSAF_PFC_UNIT_CNT_0_REG ; 
 int DSAF_PORT_DEF_VLAN_0_REG ; 
 int DSAF_PPE_INT_MSK_0_REG ; 
 int DSAF_PPE_INT_SRC_0_REG ; 
 int DSAF_PPE_INT_STS_0_REG ; 
 int DSAF_PPE_QID_CFG_0_REG ; 
 int DSAF_ROCEE_INT_MSK_0_REG ; 
 int DSAF_ROCEE_INT_SRC_0_REG ; 
 int DSAF_ROCEE_INT_STS_0_REG ; 
 int DSAF_SBM_BP_CFG_0_XGE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_1_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_2_XGE_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_3_REG_0_REG ; 
 int DSAF_SBM_BP_CFG_4_REG_0_REG ; 
 int DSAF_SBM_BP_CNT_0_0_REG ; 
 int DSAF_SBM_BP_CNT_1_0_REG ; 
 int DSAF_SBM_BP_CNT_2_0_REG ; 
 int DSAF_SBM_BP_CNT_3_0_REG ; 
 int DSAF_SBM_CFG_REG_0_REG ; 
 int DSAF_SBM_FREE_CNT_0_0_REG ; 
 int DSAF_SBM_FREE_CNT_1_0_REG ; 
 int DSAF_SBM_INER_ST_0_REG ; 
 int DSAF_SBM_INF_OUTPORT_CNT_0_REG ; 
 int DSAF_SBM_LNK_DROP_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC0_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC1_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC2_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC3_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC4_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC5_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC6_CNT_0_REG ; 
 int DSAF_SBM_LNK_INPORT_TC7_CNT_0_REG ; 
 int DSAF_SBM_LNK_RELS_CNT_0_REG ; 
 int DSAF_SBM_LNK_REQ_CNT_0_REG ; 
 int DSAF_SBM_MIB_REQ_FAILED_TC_0_REG ; 
 int DSAF_SRAM_INIT_OVER_0_REG ; 
 int DSAF_SW_PORT_NUM ; 
 int DSAF_SW_PORT_TYPE_0_REG ; 
 int DSAF_TBL_CTRL_0_REG ; 
 int DSAF_TBL_DA0_MIS_INFO0_0_REG ; 
 int DSAF_TBL_DA0_MIS_INFO1_0_REG ; 
 int DSAF_TBL_DFX_CTRL_0_REG ; 
 int DSAF_TBL_DFX_STAT_0_REG ; 
 int DSAF_TBL_DFX_STAT_2_0_REG ; 
 int DSAF_TBL_INT_MSK_0_REG ; 
 int DSAF_TBL_INT_SRC_0_REG ; 
 int DSAF_TBL_INT_STS_0_REG ; 
 int DSAF_TBL_LINE_ADDR_0_REG ; 
 int DSAF_TBL_LIN_CFG_0_REG ; 
 int DSAF_TBL_LIN_RDATA_0_REG ; 
 int DSAF_TBL_LKUP_NUM_I_0_REG ; 
 int DSAF_TBL_LKUP_NUM_O_0_REG ; 
 int DSAF_TBL_OLD_RSLT_0_REG ; 
 int DSAF_TBL_OLD_SCAN_VAL_0_REG ; 
 int DSAF_TBL_PUL_0_REG ; 
 int DSAF_TBL_SA_MIS_INFO0_0_REG ; 
 int DSAF_TBL_SA_MIS_INFO1_0_REG ; 
 int DSAF_TBL_SA_MIS_INFO2_0_REG ; 
 int DSAF_TBL_TCAM_ADDR_0_REG ; 
 int DSAF_TBL_TCAM_HIGH_0_REG ; 
 int DSAF_TBL_TCAM_LOW_0_REG ; 
 int DSAF_TBL_TCAM_MCAST_CFG_0_0_REG ; 
 int DSAF_TBL_TCAM_MCAST_CFG_1_0_REG ; 
 int DSAF_TBL_TCAM_MCAST_CFG_2_0_REG ; 
 int DSAF_TBL_TCAM_MCAST_CFG_3_0_REG ; 
 int DSAF_TBL_TCAM_MCAST_CFG_4_0_REG ; 
 int DSAF_TBL_TCAM_RAM_RDATA0_0_REG ; 
 int DSAF_TBL_TCAM_RAM_RDATA1_0_REG ; 
 int DSAF_TBL_TCAM_RAM_RDATA2_0_REG ; 
 int DSAF_TBL_TCAM_RAM_RDATA3_0_REG ; 
 int DSAF_TBL_TCAM_RAM_RDATA4_0_REG ; 
 int DSAF_TBL_TCAM_RDATA_HIGH_0_REG ; 
 int DSAF_TBL_TCAM_RDATA_LOW_0_REG ; 
 int DSAF_TBL_TCAM_UCAST_CFG_0_REG ; 
 int DSAF_TBL_UCAST_BCAST_MIS_INFO_0_0_REG ; 
 int DSAF_TOTAL_QUEUE_NUM ; 
 int DSAF_VM_DEF_VLAN_0_REG ; 
 int DSAF_VOQ_BP_ALL_THRD_0_REG ; 
 int DSAF_VOQ_BP_STATUS_0_REG ; 
 int DSAF_VOQ_ECC_ERR_ADDR_0_REG ; 
 int DSAF_VOQ_ECC_INVERT_EN_0_REG ; 
 int DSAF_VOQ_IN_PKT_NUM_0_REG ; 
 int DSAF_VOQ_NUM ; 
 int DSAF_VOQ_OUT_PKT_NUM_0_REG ; 
 int DSAF_VOQ_PPE_XOD_REQ_0_REG ; 
 int DSAF_VOQ_ROCEE_XOD_REQ_0_REG ; 
 int DSAF_VOQ_SPUP_IDLE_0_REG ; 
 int DSAF_VOQ_SRAM_PKT_NUM_0_REG ; 
 int DSAF_VOQ_XGE_XOD_REQ_0_0_REG ; 
 int DSAF_VOQ_XGE_XOD_REQ_1_0_REG ; 
 int DSAF_XGE_APP_RX_LINK_UP_0_REG ; 
 int DSAF_XGE_CTRL_SIG_CFG_0_REG ; 
 int DSAF_XGE_GE_WORK_MODE_0_REG ; 
 int DSAF_XGE_INT_MSK_0_REG ; 
 int DSAF_XGE_INT_SRC_0_REG ; 
 int DSAF_XGE_INT_STS_0_REG ; 
 int DSAF_XOD_BIG_NUM ; 
 int DSAF_XOD_CONNECT_STATE_0_REG ; 
 int DSAF_XOD_ETS_BW_OFFSET_CFG_0_REG ; 
 int DSAF_XOD_ETS_BW_TC0_TC3_CFG_0_REG ; 
 int DSAF_XOD_ETS_BW_TC4_TC7_CFG_0_REG ; 
 int DSAF_XOD_ETS_TOKEN_CFG_0_REG ; 
 int DSAF_XOD_ETS_TSA_TC0_TC3_CFG_0_REG ; 
 int DSAF_XOD_ETS_TSA_TC4_TC7_CFG_0_REG ; 
 int DSAF_XOD_FIFO_STATUS_0_REG ; 
 int DSAF_XOD_GNT_H_0_REG ; 
 int DSAF_XOD_GNT_L_0_REG ; 
 int DSAF_XOD_NUM ; 
 int DSAF_XOD_PFS_CFG_0_0_REG ; 
 int DSAF_XOD_PFS_CFG_1_0_REG ; 
 int DSAF_XOD_PFS_CFG_2_0_REG ; 
 int DSAF_XOD_PPE_RCVIN0_CNT_0_REG ; 
 int DSAF_XOD_PPE_RCVIN1_CNT_0_REG ; 
 int DSAF_XOD_RCVPKT_CNT_0_REG ; 
 int DSAF_XOD_RCVTC0_CNT_0_REG ; 
 int DSAF_XOD_RCVTC1_CNT_0_REG ; 
 int DSAF_XOD_RCVTC2_CNT_0_REG ; 
 int DSAF_XOD_RCVTC3_CNT_0_REG ; 
 int DSAF_XOD_RCVVC0_CNT_0_REG ; 
 int DSAF_XOD_RCVVC1_CNT_0_REG ; 
 int DSAF_XOD_ROCEE_RCVIN0_CNT_0_REG ; 
 int DSAF_XOD_ROCEE_RCVIN1_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN0_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN1_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN2_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN3_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN4_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN5_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN6_CNT_0_REG ; 
 int DSAF_XOD_XGE_RCVIN7_CNT_0_REG ; 
 int HNS_DSAF_SBM_NUM (struct dsaf_device*) ; 
 int dsaf_read_dev (struct dsaf_device*,int) ; 

void hns_dsaf_get_regs(struct dsaf_device *ddev, u32 port, void *data)
{
	u32 i = 0;
	u32 j;
	u32 *p = data;
	u32 reg_tmp;
	bool is_ver1 = AE_IS_VER1(ddev->dsaf_ver);

	/* dsaf common registers */
	p[0] = dsaf_read_dev(ddev, DSAF_SRAM_INIT_OVER_0_REG);
	p[1] = dsaf_read_dev(ddev, DSAF_CFG_0_REG);
	p[2] = dsaf_read_dev(ddev, DSAF_ECC_ERR_INVERT_0_REG);
	p[3] = dsaf_read_dev(ddev, DSAF_ABNORMAL_TIMEOUT_0_REG);
	p[4] = dsaf_read_dev(ddev, DSAF_FSM_TIMEOUT_0_REG);
	p[5] = dsaf_read_dev(ddev, DSAF_DSA_REG_CNT_CLR_CE_REG);
	p[6] = dsaf_read_dev(ddev, DSAF_DSA_SBM_INF_FIFO_THRD_REG);
	p[7] = dsaf_read_dev(ddev, DSAF_DSA_SRAM_1BIT_ECC_SEL_REG);
	p[8] = dsaf_read_dev(ddev, DSAF_DSA_SRAM_1BIT_ECC_CNT_REG);

	p[9] = dsaf_read_dev(ddev, DSAF_PFC_EN_0_REG + port * 4);
	p[10] = dsaf_read_dev(ddev, DSAF_PFC_UNIT_CNT_0_REG + port * 4);
	p[11] = dsaf_read_dev(ddev, DSAF_XGE_INT_MSK_0_REG + port * 4);
	p[12] = dsaf_read_dev(ddev, DSAF_XGE_INT_SRC_0_REG + port * 4);
	p[13] = dsaf_read_dev(ddev, DSAF_XGE_INT_STS_0_REG + port * 4);
	p[14] = dsaf_read_dev(ddev, DSAF_XGE_INT_MSK_0_REG + port * 4);
	p[15] = dsaf_read_dev(ddev, DSAF_PPE_INT_MSK_0_REG + port * 4);
	p[16] = dsaf_read_dev(ddev, DSAF_ROCEE_INT_MSK_0_REG + port * 4);
	p[17] = dsaf_read_dev(ddev, DSAF_XGE_INT_SRC_0_REG + port * 4);
	p[18] = dsaf_read_dev(ddev, DSAF_PPE_INT_SRC_0_REG + port * 4);
	p[19] =  dsaf_read_dev(ddev, DSAF_ROCEE_INT_SRC_0_REG + port * 4);
	p[20] = dsaf_read_dev(ddev, DSAF_XGE_INT_STS_0_REG + port * 4);
	p[21] = dsaf_read_dev(ddev, DSAF_PPE_INT_STS_0_REG + port * 4);
	p[22] = dsaf_read_dev(ddev, DSAF_ROCEE_INT_STS_0_REG + port * 4);
	p[23] = dsaf_read_dev(ddev, DSAF_PPE_QID_CFG_0_REG + port * 4);

	for (i = 0; i < DSAF_SW_PORT_NUM; i++)
		p[24 + i] = dsaf_read_dev(ddev,
				DSAF_SW_PORT_TYPE_0_REG + i * 4);

	p[32] = dsaf_read_dev(ddev, DSAF_MIX_DEF_QID_0_REG + port * 4);

	for (i = 0; i < DSAF_SW_PORT_NUM; i++)
		p[33 + i] = dsaf_read_dev(ddev,
				DSAF_PORT_DEF_VLAN_0_REG + i * 4);

	for (i = 0; i < DSAF_TOTAL_QUEUE_NUM; i++)
		p[41 + i] = dsaf_read_dev(ddev,
				DSAF_VM_DEF_VLAN_0_REG + i * 4);

	/* dsaf inode registers */
	p[170] = dsaf_read_dev(ddev, DSAF_INODE_CUT_THROUGH_CFG_0_REG);

	p[171] = dsaf_read_dev(ddev,
			DSAF_INODE_ECC_ERR_ADDR_0_REG + port * 0x80);

	for (i = 0; i < DSAF_INODE_NUM / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + port;
		p[172 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_IN_PORT_NUM_0_REG + j * 0x80);
		p[175 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_PRI_TC_CFG_0_REG + j * 0x80);
		p[178 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_BP_STATUS_0_REG + j * 0x80);
		p[181 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_PAD_DISCARD_NUM_0_REG + j * 0x80);
		p[184 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_FINAL_IN_MAN_NUM_0_REG + j * 0x80);
		p[187 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_FINAL_IN_PKT_NUM_0_REG + j * 0x80);
		p[190 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_SBM_PID_NUM_0_REG + j * 0x80);
		reg_tmp = is_ver1 ? DSAF_INODE_FINAL_IN_PAUSE_NUM_0_REG :
				    DSAFV2_INODE_FINAL_IN_PAUSE_NUM_0_REG;
		p[193 + i] = dsaf_read_dev(ddev, reg_tmp + j * 0x80);
		p[196 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_SBM_RELS_NUM_0_REG + j * 0x80);
		p[199 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_SBM_DROP_NUM_0_REG + j * 0x80);
		p[202 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_CRC_FALSE_NUM_0_REG + j * 0x80);
		p[205 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_BP_DISCARD_NUM_0_REG + j * 0x80);
		p[208 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_RSLT_DISCARD_NUM_0_REG + j * 0x80);
		p[211 + i] = dsaf_read_dev(ddev,
			DSAF_INODE_LOCAL_ADDR_FALSE_NUM_0_REG + j * 0x80);
		p[214 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_VOQ_OVER_NUM_0_REG + j * 0x80);
		p[217 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_BD_SAVE_STATUS_0_REG + j * 4);
		p[220 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_BD_ORDER_STATUS_0_REG + j * 4);
		p[223 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_SW_VLAN_TAG_DISC_0_REG + j * 4);
		p[226 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_IN_DATA_STP_DISC_0_REG + j * 4);
	}

	p[229] = dsaf_read_dev(ddev, DSAF_INODE_GE_FC_EN_0_REG + port * 4);

	for (i = 0; i < DSAF_INODE_NUM / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + port;
		p[230 + i] = dsaf_read_dev(ddev,
				DSAF_INODE_VC0_IN_PKT_NUM_0_REG + j * 4);
	}

	p[233] = dsaf_read_dev(ddev,
		DSAF_INODE_VC1_IN_PKT_NUM_0_REG + port * 0x80);

	/* dsaf inode registers */
	for (i = 0; i < HNS_DSAF_SBM_NUM(ddev) / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + port;
		p[234 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_CFG_REG_0_REG + j * 0x80);
		p[237 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CFG_0_XGE_REG_0_REG + j * 0x80);
		p[240 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CFG_1_REG_0_REG + j * 0x80);
		p[243 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CFG_2_XGE_REG_0_REG + j * 0x80);
		p[246 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_FREE_CNT_0_0_REG + j * 0x80);
		p[249 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_FREE_CNT_1_0_REG + j * 0x80);
		p[252 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CNT_0_0_REG + j * 0x80);
		p[255 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CNT_1_0_REG + j * 0x80);
		p[258 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CNT_2_0_REG + j * 0x80);
		p[261 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CNT_3_0_REG + j * 0x80);
		p[264 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_INER_ST_0_REG + j * 0x80);
		p[267 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_MIB_REQ_FAILED_TC_0_REG + j * 0x80);
		p[270 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_CNT_0_REG + j * 0x80);
		p[273 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_DROP_CNT_0_REG + j * 0x80);
		p[276 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_INF_OUTPORT_CNT_0_REG + j * 0x80);
		p[279 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC0_CNT_0_REG + j * 0x80);
		p[282 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC1_CNT_0_REG + j * 0x80);
		p[285 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC2_CNT_0_REG + j * 0x80);
		p[288 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC3_CNT_0_REG + j * 0x80);
		p[291 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC4_CNT_0_REG + j * 0x80);
		p[294 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC5_CNT_0_REG + j * 0x80);
		p[297 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC6_CNT_0_REG + j * 0x80);
		p[300 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC7_CNT_0_REG + j * 0x80);
		p[303 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_REQ_CNT_0_REG + j * 0x80);
		p[306 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_LNK_RELS_CNT_0_REG + j * 0x80);
		p[309 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CFG_3_REG_0_REG + j * 0x80);
		p[312 + i] = dsaf_read_dev(ddev,
				DSAF_SBM_BP_CFG_4_REG_0_REG + j * 0x80);
	}

	/* dsaf onode registers */
	for (i = 0; i < DSAF_XOD_NUM; i++) {
		p[315 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_ETS_TSA_TC0_TC3_CFG_0_REG + i * 0x90);
		p[323 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_ETS_TSA_TC4_TC7_CFG_0_REG + i * 0x90);
		p[331 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_ETS_BW_TC0_TC3_CFG_0_REG + i * 0x90);
		p[339 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_ETS_BW_TC4_TC7_CFG_0_REG + i * 0x90);
		p[347 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_ETS_BW_OFFSET_CFG_0_REG + i * 0x90);
		p[355 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_ETS_TOKEN_CFG_0_REG + i * 0x90);
	}

	p[363] = dsaf_read_dev(ddev, DSAF_XOD_PFS_CFG_0_0_REG + port * 0x90);
	p[364] = dsaf_read_dev(ddev, DSAF_XOD_PFS_CFG_1_0_REG + port * 0x90);
	p[365] = dsaf_read_dev(ddev, DSAF_XOD_PFS_CFG_2_0_REG + port * 0x90);

	for (i = 0; i < DSAF_XOD_BIG_NUM / DSAF_COMM_CHN; i++) {
		j = i * DSAF_COMM_CHN + port;
		p[366 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_GNT_L_0_REG + j * 0x90);
		p[369 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_GNT_H_0_REG + j * 0x90);
		p[372 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_CONNECT_STATE_0_REG + j * 0x90);
		p[375 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVPKT_CNT_0_REG + j * 0x90);
		p[378 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVTC0_CNT_0_REG + j * 0x90);
		p[381 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVTC1_CNT_0_REG + j * 0x90);
		p[384 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVTC2_CNT_0_REG + j * 0x90);
		p[387 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVTC3_CNT_0_REG + j * 0x90);
		p[390 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVVC0_CNT_0_REG + j * 0x90);
		p[393 + i] = dsaf_read_dev(ddev,
				DSAF_XOD_RCVVC1_CNT_0_REG + j * 0x90);
	}

	p[396] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN0_CNT_0_REG + port * 0x90);
	p[397] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN1_CNT_0_REG + port * 0x90);
	p[398] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN2_CNT_0_REG + port * 0x90);
	p[399] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN3_CNT_0_REG + port * 0x90);
	p[400] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN4_CNT_0_REG + port * 0x90);
	p[401] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN5_CNT_0_REG + port * 0x90);
	p[402] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN6_CNT_0_REG + port * 0x90);
	p[403] = dsaf_read_dev(ddev,
		DSAF_XOD_XGE_RCVIN7_CNT_0_REG + port * 0x90);
	p[404] = dsaf_read_dev(ddev,
		DSAF_XOD_PPE_RCVIN0_CNT_0_REG + port * 0x90);
	p[405] = dsaf_read_dev(ddev,
		DSAF_XOD_PPE_RCVIN1_CNT_0_REG + port * 0x90);
	p[406] = dsaf_read_dev(ddev,
		DSAF_XOD_ROCEE_RCVIN0_CNT_0_REG + port * 0x90);
	p[407] = dsaf_read_dev(ddev,
		DSAF_XOD_ROCEE_RCVIN1_CNT_0_REG + port * 0x90);
	p[408] = dsaf_read_dev(ddev,
		DSAF_XOD_FIFO_STATUS_0_REG + port * 0x90);

	/* dsaf voq registers */
	for (i = 0; i < DSAF_VOQ_NUM / DSAF_COMM_CHN; i++) {
		j = (i * DSAF_COMM_CHN + port) * 0x90;
		p[409 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_ECC_INVERT_EN_0_REG + j);
		p[412 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_SRAM_PKT_NUM_0_REG + j);
		p[415 + i] = dsaf_read_dev(ddev, DSAF_VOQ_IN_PKT_NUM_0_REG + j);
		p[418 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_OUT_PKT_NUM_0_REG + j);
		p[421 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_ECC_ERR_ADDR_0_REG + j);
		p[424 + i] = dsaf_read_dev(ddev, DSAF_VOQ_BP_STATUS_0_REG + j);
		p[427 + i] = dsaf_read_dev(ddev, DSAF_VOQ_SPUP_IDLE_0_REG + j);
		p[430 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_XGE_XOD_REQ_0_0_REG + j);
		p[433 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_XGE_XOD_REQ_1_0_REG + j);
		p[436 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_PPE_XOD_REQ_0_REG + j);
		p[439 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_ROCEE_XOD_REQ_0_REG + j);
		p[442 + i] = dsaf_read_dev(ddev,
			DSAF_VOQ_BP_ALL_THRD_0_REG + j);
	}

	/* dsaf tbl registers */
	p[445] = dsaf_read_dev(ddev, DSAF_TBL_CTRL_0_REG);
	p[446] = dsaf_read_dev(ddev, DSAF_TBL_INT_MSK_0_REG);
	p[447] = dsaf_read_dev(ddev, DSAF_TBL_INT_SRC_0_REG);
	p[448] = dsaf_read_dev(ddev, DSAF_TBL_INT_STS_0_REG);
	p[449] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_ADDR_0_REG);
	p[450] = dsaf_read_dev(ddev, DSAF_TBL_LINE_ADDR_0_REG);
	p[451] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_HIGH_0_REG);
	p[452] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_LOW_0_REG);
	p[453] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG);
	p[454] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_3_0_REG);
	p[455] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_2_0_REG);
	p[456] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_1_0_REG);
	p[457] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_0_0_REG);
	p[458] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_UCAST_CFG_0_REG);
	p[459] = dsaf_read_dev(ddev, DSAF_TBL_LIN_CFG_0_REG);
	p[460] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RDATA_HIGH_0_REG);
	p[461] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RDATA_LOW_0_REG);
	p[462] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA4_0_REG);
	p[463] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA3_0_REG);
	p[464] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA2_0_REG);
	p[465] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA1_0_REG);
	p[466] = dsaf_read_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA0_0_REG);
	p[467] = dsaf_read_dev(ddev, DSAF_TBL_LIN_RDATA_0_REG);

	for (i = 0; i < DSAF_SW_PORT_NUM; i++) {
		j = i * 0x8;
		p[468 + 2 * i] = dsaf_read_dev(ddev,
			DSAF_TBL_DA0_MIS_INFO1_0_REG + j);
		p[469 + 2 * i] = dsaf_read_dev(ddev,
			DSAF_TBL_DA0_MIS_INFO0_0_REG + j);
	}

	p[484] = dsaf_read_dev(ddev, DSAF_TBL_SA_MIS_INFO2_0_REG);
	p[485] = dsaf_read_dev(ddev, DSAF_TBL_SA_MIS_INFO1_0_REG);
	p[486] = dsaf_read_dev(ddev, DSAF_TBL_SA_MIS_INFO0_0_REG);
	p[487] = dsaf_read_dev(ddev, DSAF_TBL_PUL_0_REG);
	p[488] = dsaf_read_dev(ddev, DSAF_TBL_OLD_RSLT_0_REG);
	p[489] = dsaf_read_dev(ddev, DSAF_TBL_OLD_SCAN_VAL_0_REG);
	p[490] = dsaf_read_dev(ddev, DSAF_TBL_DFX_CTRL_0_REG);
	p[491] = dsaf_read_dev(ddev, DSAF_TBL_DFX_STAT_0_REG);
	p[492] = dsaf_read_dev(ddev, DSAF_TBL_DFX_STAT_2_0_REG);
	p[493] = dsaf_read_dev(ddev, DSAF_TBL_LKUP_NUM_I_0_REG);
	p[494] = dsaf_read_dev(ddev, DSAF_TBL_LKUP_NUM_O_0_REG);
	p[495] = dsaf_read_dev(ddev, DSAF_TBL_UCAST_BCAST_MIS_INFO_0_0_REG);

	/* dsaf other registers */
	p[496] = dsaf_read_dev(ddev, DSAF_INODE_FIFO_WL_0_REG + port * 0x4);
	p[497] = dsaf_read_dev(ddev, DSAF_ONODE_FIFO_WL_0_REG + port * 0x4);
	p[498] = dsaf_read_dev(ddev, DSAF_XGE_GE_WORK_MODE_0_REG + port * 0x4);
	p[499] = dsaf_read_dev(ddev,
		DSAF_XGE_APP_RX_LINK_UP_0_REG + port * 0x4);
	p[500] = dsaf_read_dev(ddev, DSAF_NETPORT_CTRL_SIG_0_REG + port * 0x4);
	p[501] = dsaf_read_dev(ddev, DSAF_XGE_CTRL_SIG_CFG_0_REG + port * 0x4);

	if (!is_ver1)
		p[502] = dsaf_read_dev(ddev, DSAF_PAUSE_CFG_REG + port * 0x4);

	/* mark end of dsaf regs */
	for (i = 503; i < 504; i++)
		p[i] = 0xdddddddd;
}