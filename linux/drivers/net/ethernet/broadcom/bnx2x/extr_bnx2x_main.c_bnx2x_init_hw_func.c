#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct bnx2x_ilt {TYPE_3__* lines; TYPE_2__* clients; } ;
struct TYPE_5__ {scalar_t__ int_block; } ;
struct bnx2x {int flags; int dmae_ready; int mf_ov; int igu_sb_cnt; int igu_base_sb; int igu_dsb_id; int /*<<< orphan*/  link_params; TYPE_1__ common; TYPE_4__* context; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  cxt_mapping; int /*<<< orphan*/  vcxt; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  page_mapping; int /*<<< orphan*/  page; } ;
struct TYPE_6__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTENTION_ID ; 
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int /*<<< orphan*/  BLOCK_ATC ; 
 int /*<<< orphan*/  BLOCK_BRB1 ; 
 int /*<<< orphan*/  BLOCK_CCM ; 
 int /*<<< orphan*/  BLOCK_CDU ; 
 int /*<<< orphan*/  BLOCK_CFC ; 
 int /*<<< orphan*/  BLOCK_CSDM ; 
 int /*<<< orphan*/  BLOCK_CSEM ; 
 int /*<<< orphan*/  BLOCK_DMAE ; 
 int /*<<< orphan*/  BLOCK_DORQ ; 
 int /*<<< orphan*/  BLOCK_HC ; 
 int /*<<< orphan*/  BLOCK_IGU ; 
 int /*<<< orphan*/  BLOCK_MISC ; 
 int /*<<< orphan*/  BLOCK_MISC_AEU ; 
 int /*<<< orphan*/  BLOCK_NIG ; 
 int /*<<< orphan*/  BLOCK_PBF ; 
 int /*<<< orphan*/  BLOCK_PGLUE_B ; 
 int /*<<< orphan*/  BLOCK_PRS ; 
 int /*<<< orphan*/  BLOCK_PXP ; 
 int /*<<< orphan*/  BLOCK_PXP2 ; 
 int /*<<< orphan*/  BLOCK_QM ; 
 int /*<<< orphan*/  BLOCK_SRC ; 
 int /*<<< orphan*/  BLOCK_TCM ; 
 int /*<<< orphan*/  BLOCK_TM ; 
 int /*<<< orphan*/  BLOCK_TSDM ; 
 int /*<<< orphan*/  BLOCK_TSEM ; 
 int /*<<< orphan*/  BLOCK_UCM ; 
 int /*<<< orphan*/  BLOCK_UPB ; 
 int /*<<< orphan*/  BLOCK_USDM ; 
 int /*<<< orphan*/  BLOCK_USEM ; 
 int /*<<< orphan*/  BLOCK_XCM ; 
 int /*<<< orphan*/  BLOCK_XPB ; 
 int /*<<< orphan*/  BLOCK_XSDM ; 
 int /*<<< orphan*/  BLOCK_XSEM ; 
 int BNX2X_FIRST_VF_CID ; 
 scalar_t__ BNX2X_IS_MF_SD_PROTOCOL_FCOE (struct bnx2x*) ; 
 int BNX2X_MAX_NUM_OF_VFS ; 
 int BP_FUNC (struct bnx2x*) ; 
 struct bnx2x_ilt* BP_ILT (struct bnx2x*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int BP_VN (struct bnx2x*) ; 
 int CFC_REG_WEAK_ENABLE_PF ; 
 scalar_t__ CHIP_INT_MODE_IS_BC (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_MODE_IS_4_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CONFIGURE_NIC_MODE (struct bnx2x*) ; 
 int CSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  CSTORM_ID ; 
 scalar_t__ CSTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int DORQ_REG_MODE_ACT ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int E1HVN_MAX ; 
 int HC_CONFIG_0_REG_MSI_ATTN_EN_0 ; 
 int HC_REG_CONFIG_0 ; 
 int HC_REG_CONFIG_1 ; 
 int HC_REG_HC_PRTY_STS_CLR ; 
 int HC_REG_LEADING_EDGE_0 ; 
 int HC_REG_MAIN_MEMORY ; 
 int HC_REG_MAIN_MEMORY_SIZE ; 
 int HC_REG_TRAILING_EDGE_0 ; 
 int IGU_BC_BASE_DSB_PROD ; 
 int IGU_BC_DSB_NUM_SEGS ; 
 int IGU_BC_NDSB_NUM_SEGS ; 
 int /*<<< orphan*/  IGU_INT_NOP ; 
 int IGU_NORM_BASE_DSB_PROD ; 
 int IGU_NORM_DSB_NUM_SEGS ; 
 int IGU_NORM_NDSB_NUM_SEGS ; 
 int IGU_PF_CONF_FUNC_EN ; 
 int IGU_PF_CONF_SINGLE_ISR_EN ; 
 int IGU_REG_LEADING_EDGE_LATCH ; 
 int IGU_REG_PBA_STATUS_LSB ; 
 int IGU_REG_PBA_STATUS_MSB ; 
 int IGU_REG_PF_CONFIGURATION ; 
 int IGU_REG_PROD_CONS_MEMORY ; 
 int IGU_REG_SB_INT_BEFORE_MASK_LSB ; 
 int IGU_REG_SB_INT_BEFORE_MASK_MSB ; 
 int IGU_REG_SB_MASK_LSB ; 
 int IGU_REG_SB_MASK_MSB ; 
 int IGU_REG_TRAILING_EDGE_LATCH ; 
 size_t ILT_CLIENT_CDU ; 
 int ILT_PAGE_CIDS ; 
 int /*<<< orphan*/  INITOP_SET ; 
 scalar_t__ INT_BLOCK_HC ; 
 scalar_t__ IS_MF (struct bnx2x*) ; 
 scalar_t__ IS_MF_UFP (struct bnx2x*) ; 
 scalar_t__ IS_SRIOV (struct bnx2x*) ; 
 int L2_ILT_LINES (struct bnx2x*) ; 
 int MISC_REG_AEU_GENERAL_ATTN_12 ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int NIG_REG_LLH0_FUNC_EN ; 
 int NIG_REG_LLH0_FUNC_VLAN_ID ; 
 int PBF_REG_DISABLE_PF ; 
 int PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int PHASE_PF0 ; 
 int PRS_REG_NIC_MODE ; 
 int QM_REG_PF_EN ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  REG_WR8 (struct bnx2x*,scalar_t__,int) ; 
 int TSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  TSTORM_ID ; 
 scalar_t__ TSTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int USEM_REG_VFPF_ERR_NUM ; 
 int USING_MSIX_FLAG ; 
 int /*<<< orphan*/  USTORM_ID ; 
 scalar_t__ USTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int XSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  XSTORM_ID ; 
 scalar_t__ XSTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int /*<<< orphan*/  bnx2x_ack_sb (struct bnx2x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_clean_pglue_errors (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_fw_dump (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_igu_clear_sb (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_ilt_init_op (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_block (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_init_searcher (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_iov_init_dq (struct bnx2x*) ; 
 int bnx2x_iov_init_ilt (struct bnx2x*,int) ; 
 int bnx2x_pf_flr_clnup (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_phy_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_read_dmae (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_write_dmae (struct bnx2x*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  wb_data ; 

__attribute__((used)) static int bnx2x_init_hw_func(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	int func = BP_FUNC(bp);
	int init_phase = PHASE_PF0 + func;
	struct bnx2x_ilt *ilt = BP_ILT(bp);
	u16 cdu_ilt_start;
	u32 addr, val;
	u32 main_mem_base, main_mem_size, main_mem_prty_clr;
	int i, main_mem_width, rc;

	DP(NETIF_MSG_HW, "starting func init  func %d\n", func);

	/* FLR cleanup - hmmm */
	if (!CHIP_IS_E1x(bp)) {
		rc = bnx2x_pf_flr_clnup(bp);
		if (rc) {
			bnx2x_fw_dump(bp);
			return rc;
		}
	}

	/* set MSI reconfigure capability */
	if (bp->common.int_block == INT_BLOCK_HC) {
		addr = (port ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0);
		val = REG_RD(bp, addr);
		val |= HC_CONFIG_0_REG_MSI_ATTN_EN_0;
		REG_WR(bp, addr, val);
	}

	bnx2x_init_block(bp, BLOCK_PXP, init_phase);
	bnx2x_init_block(bp, BLOCK_PXP2, init_phase);

	ilt = BP_ILT(bp);
	cdu_ilt_start = ilt->clients[ILT_CLIENT_CDU].start;

	if (IS_SRIOV(bp))
		cdu_ilt_start += BNX2X_FIRST_VF_CID/ILT_PAGE_CIDS;
	cdu_ilt_start = bnx2x_iov_init_ilt(bp, cdu_ilt_start);

	/* since BNX2X_FIRST_VF_CID > 0 the PF L2 cids precedes
	 * those of the VFs, so start line should be reset
	 */
	cdu_ilt_start = ilt->clients[ILT_CLIENT_CDU].start;
	for (i = 0; i < L2_ILT_LINES(bp); i++) {
		ilt->lines[cdu_ilt_start + i].page = bp->context[i].vcxt;
		ilt->lines[cdu_ilt_start + i].page_mapping =
			bp->context[i].cxt_mapping;
		ilt->lines[cdu_ilt_start + i].size = bp->context[i].size;
	}

	bnx2x_ilt_init_op(bp, INITOP_SET);

	if (!CONFIGURE_NIC_MODE(bp)) {
		bnx2x_init_searcher(bp);
		REG_WR(bp, PRS_REG_NIC_MODE, 0);
		DP(NETIF_MSG_IFUP, "NIC MODE disabled\n");
	} else {
		/* Set NIC mode */
		REG_WR(bp, PRS_REG_NIC_MODE, 1);
		DP(NETIF_MSG_IFUP, "NIC MODE configured\n");
	}

	if (!CHIP_IS_E1x(bp)) {
		u32 pf_conf = IGU_PF_CONF_FUNC_EN;

		/* Turn on a single ISR mode in IGU if driver is going to use
		 * INT#x or MSI
		 */
		if (!(bp->flags & USING_MSIX_FLAG))
			pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		/*
		 * Timers workaround bug: function init part.
		 * Need to wait 20msec after initializing ILT,
		 * needed to make sure there are no requests in
		 * one of the PXP internal queues with "old" ILT addresses
		 */
		msleep(20);
		/*
		 * Master enable - Due to WB DMAE writes performed before this
		 * register is re-initialized as part of the regular function
		 * init
		 */
		REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);
		/* Enable the function in IGU */
		REG_WR(bp, IGU_REG_PF_CONFIGURATION, pf_conf);
	}

	bp->dmae_ready = 1;

	bnx2x_init_block(bp, BLOCK_PGLUE_B, init_phase);

	bnx2x_clean_pglue_errors(bp);

	bnx2x_init_block(bp, BLOCK_ATC, init_phase);
	bnx2x_init_block(bp, BLOCK_DMAE, init_phase);
	bnx2x_init_block(bp, BLOCK_NIG, init_phase);
	bnx2x_init_block(bp, BLOCK_SRC, init_phase);
	bnx2x_init_block(bp, BLOCK_MISC, init_phase);
	bnx2x_init_block(bp, BLOCK_TCM, init_phase);
	bnx2x_init_block(bp, BLOCK_UCM, init_phase);
	bnx2x_init_block(bp, BLOCK_CCM, init_phase);
	bnx2x_init_block(bp, BLOCK_XCM, init_phase);
	bnx2x_init_block(bp, BLOCK_TSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_USEM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSEM, init_phase);

	if (!CHIP_IS_E1x(bp))
		REG_WR(bp, QM_REG_PF_EN, 1);

	if (!CHIP_IS_E1x(bp)) {
		REG_WR(bp, TSEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
		REG_WR(bp, USEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
		REG_WR(bp, CSEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
		REG_WR(bp, XSEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
	}
	bnx2x_init_block(bp, BLOCK_QM, init_phase);

	bnx2x_init_block(bp, BLOCK_TM, init_phase);
	bnx2x_init_block(bp, BLOCK_DORQ, init_phase);
	REG_WR(bp, DORQ_REG_MODE_ACT, 1); /* no dpm */

	bnx2x_iov_init_dq(bp);

	bnx2x_init_block(bp, BLOCK_BRB1, init_phase);
	bnx2x_init_block(bp, BLOCK_PRS, init_phase);
	bnx2x_init_block(bp, BLOCK_TSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_USDM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_UPB, init_phase);
	bnx2x_init_block(bp, BLOCK_XPB, init_phase);
	bnx2x_init_block(bp, BLOCK_PBF, init_phase);
	if (!CHIP_IS_E1x(bp))
		REG_WR(bp, PBF_REG_DISABLE_PF, 0);

	bnx2x_init_block(bp, BLOCK_CDU, init_phase);

	bnx2x_init_block(bp, BLOCK_CFC, init_phase);

	if (!CHIP_IS_E1x(bp))
		REG_WR(bp, CFC_REG_WEAK_ENABLE_PF, 1);

	if (IS_MF(bp)) {
		if (!(IS_MF_UFP(bp) && BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp))) {
			REG_WR(bp, NIG_REG_LLH0_FUNC_EN + port * 8, 1);
			REG_WR(bp, NIG_REG_LLH0_FUNC_VLAN_ID + port * 8,
			       bp->mf_ov);
		}
	}

	bnx2x_init_block(bp, BLOCK_MISC_AEU, init_phase);

	/* HC init per function */
	if (bp->common.int_block == INT_BLOCK_HC) {
		if (CHIP_IS_E1H(bp)) {
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);

			REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, 0);
			REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, 0);
		}
		bnx2x_init_block(bp, BLOCK_HC, init_phase);

	} else {
		int num_segs, sb_idx, prod_offset;

		REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);

		if (!CHIP_IS_E1x(bp)) {
			REG_WR(bp, IGU_REG_LEADING_EDGE_LATCH, 0);
			REG_WR(bp, IGU_REG_TRAILING_EDGE_LATCH, 0);
		}

		bnx2x_init_block(bp, BLOCK_IGU, init_phase);

		if (!CHIP_IS_E1x(bp)) {
			int dsb_idx = 0;
			/**
			 * Producer memory:
			 * E2 mode: address 0-135 match to the mapping memory;
			 * 136 - PF0 default prod; 137 - PF1 default prod;
			 * 138 - PF2 default prod; 139 - PF3 default prod;
			 * 140 - PF0 attn prod;    141 - PF1 attn prod;
			 * 142 - PF2 attn prod;    143 - PF3 attn prod;
			 * 144-147 reserved.
			 *
			 * E1.5 mode - In backward compatible mode;
			 * for non default SB; each even line in the memory
			 * holds the U producer and each odd line hold
			 * the C producer. The first 128 producers are for
			 * NDSB (PF0 - 0-31; PF1 - 32-63 and so on). The last 20
			 * producers are for the DSB for each PF.
			 * Each PF has five segments: (the order inside each
			 * segment is PF0; PF1; PF2; PF3) - 128-131 U prods;
			 * 132-135 C prods; 136-139 X prods; 140-143 T prods;
			 * 144-147 attn prods;
			 */
			/* non-default-status-blocks */
			num_segs = CHIP_INT_MODE_IS_BC(bp) ?
				IGU_BC_NDSB_NUM_SEGS : IGU_NORM_NDSB_NUM_SEGS;
			for (sb_idx = 0; sb_idx < bp->igu_sb_cnt; sb_idx++) {
				prod_offset = (bp->igu_base_sb + sb_idx) *
					num_segs;

				for (i = 0; i < num_segs; i++) {
					addr = IGU_REG_PROD_CONS_MEMORY +
							(prod_offset + i) * 4;
					REG_WR(bp, addr, 0);
				}
				/* send consumer update with value 0 */
				bnx2x_ack_sb(bp, bp->igu_base_sb + sb_idx,
					     USTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_igu_clear_sb(bp,
						   bp->igu_base_sb + sb_idx);
			}

			/* default-status-blocks */
			num_segs = CHIP_INT_MODE_IS_BC(bp) ?
				IGU_BC_DSB_NUM_SEGS : IGU_NORM_DSB_NUM_SEGS;

			if (CHIP_MODE_IS_4_PORT(bp))
				dsb_idx = BP_FUNC(bp);
			else
				dsb_idx = BP_VN(bp);

			prod_offset = (CHIP_INT_MODE_IS_BC(bp) ?
				       IGU_BC_BASE_DSB_PROD + dsb_idx :
				       IGU_NORM_BASE_DSB_PROD + dsb_idx);

			/*
			 * igu prods come in chunks of E1HVN_MAX (4) -
			 * does not matters what is the current chip mode
			 */
			for (i = 0; i < (num_segs * E1HVN_MAX);
			     i += E1HVN_MAX) {
				addr = IGU_REG_PROD_CONS_MEMORY +
							(prod_offset + i)*4;
				REG_WR(bp, addr, 0);
			}
			/* send consumer update with 0 */
			if (CHIP_INT_MODE_IS_BC(bp)) {
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     USTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     CSTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     XSTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     TSTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     ATTENTION_ID, 0, IGU_INT_NOP, 1);
			} else {
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     USTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     ATTENTION_ID, 0, IGU_INT_NOP, 1);
			}
			bnx2x_igu_clear_sb(bp, bp->igu_dsb_id);

			/* !!! These should become driver const once
			   rf-tool supports split-68 const */
			REG_WR(bp, IGU_REG_SB_INT_BEFORE_MASK_LSB, 0);
			REG_WR(bp, IGU_REG_SB_INT_BEFORE_MASK_MSB, 0);
			REG_WR(bp, IGU_REG_SB_MASK_LSB, 0);
			REG_WR(bp, IGU_REG_SB_MASK_MSB, 0);
			REG_WR(bp, IGU_REG_PBA_STATUS_LSB, 0);
			REG_WR(bp, IGU_REG_PBA_STATUS_MSB, 0);
		}
	}

	/* Reset PCIE errors for debug */
	REG_WR(bp, 0x2114, 0xffffffff);
	REG_WR(bp, 0x2120, 0xffffffff);

	if (CHIP_IS_E1x(bp)) {
		main_mem_size = HC_REG_MAIN_MEMORY_SIZE / 2; /*dwords*/
		main_mem_base = HC_REG_MAIN_MEMORY +
				BP_PORT(bp) * (main_mem_size * 4);
		main_mem_prty_clr = HC_REG_HC_PRTY_STS_CLR;
		main_mem_width = 8;

		val = REG_RD(bp, main_mem_prty_clr);
		if (val)
			DP(NETIF_MSG_HW,
			   "Hmmm... Parity errors in HC block during function init (0x%x)!\n",
			   val);

		/* Clear "false" parity errors in MSI-X table */
		for (i = main_mem_base;
		     i < main_mem_base + main_mem_size * 4;
		     i += main_mem_width) {
			bnx2x_read_dmae(bp, i, main_mem_width / 4);
			bnx2x_write_dmae(bp, bnx2x_sp_mapping(bp, wb_data),
					 i, main_mem_width / 4);
		}
		/* Clear HC parity attention */
		REG_RD(bp, main_mem_prty_clr);
	}

#ifdef BNX2X_STOP_ON_ERROR
	/* Enable STORMs SP logging */
	REG_WR8(bp, BAR_USTRORM_INTMEM +
	       USTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
	REG_WR8(bp, BAR_TSTRORM_INTMEM +
	       TSTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
	REG_WR8(bp, BAR_CSTRORM_INTMEM +
	       CSTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
	REG_WR8(bp, BAR_XSTRORM_INTMEM +
	       XSTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
#endif

	bnx2x_phy_probe(&bp->link_params);

	return 0;
}