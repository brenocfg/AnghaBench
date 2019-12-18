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
typedef  union cdu_context {int dummy; } cdu_context ;
typedef  int u8 ;
typedef  int u32 ;
struct ilt_client_info {int /*<<< orphan*/  client_num; scalar_t__ end; scalar_t__ start; } ;
struct bnx2x_ilt {int /*<<< orphan*/  client_num; scalar_t__ end; scalar_t__ start; } ;
struct bnx2x {int dmae_ready; int path_has_ovlan; TYPE_1__* pdev; int /*<<< orphan*/  qm_cid_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATC_REG_ATC_INIT_DONE ; 
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
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int BNX2X_PXP_DRAM_ALIGN ; 
 int BP_ABS_FUNC (struct bnx2x*) ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 int BP_PATH (struct bnx2x*) ; 
 int CDU_REG_CDU_GLOBAL_PARAMS ; 
 int /*<<< orphan*/  CFC_REG_AC_INIT_DONE ; 
 int /*<<< orphan*/  CFC_REG_CAM_INIT_DONE ; 
 int CFC_REG_CFC_INT_MASK ; 
 int CFC_REG_DEBUG0 ; 
 int CFC_REG_INIT_REG ; 
 int /*<<< orphan*/  CFC_REG_LL_INIT_DONE ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E3B0 (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_EMUL (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 scalar_t__ CNIC_SUPPORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CSEM_REG_PASSIVE_BUFFER ; 
 int DORQ_REG_DORQ_INT_MASK ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int E2_FUNC_MAX ; 
 int EBUSY ; 
 int GRCBASE_MISC ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_RESET ; 
 int IGU_REG_RESET_MEMORIES ; 
 int /*<<< orphan*/  ILT_CLIENT_TM ; 
 scalar_t__ ILT_NUM_PAGE_ENTRIES ; 
 int /*<<< orphan*/  INITOP_CLEAR ; 
 int /*<<< orphan*/  INITOP_SET ; 
 int IS_MF (struct bnx2x*) ; 
 scalar_t__ IS_MF_AFEX (struct bnx2x*) ; 
 int IS_MF_SD (struct bnx2x*) ; 
 int MISC_REGISTERS_RESET_REG_1_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_1_SET ; 
 int MISC_REGISTERS_RESET_REG_2_MSTAT0 ; 
 int MISC_REGISTERS_RESET_REG_2_MSTAT1 ; 
 int MISC_REGISTERS_RESET_REG_2_SET ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int NIG_REG_LLH_E1HOV_MODE ; 
 int NIG_REG_LLH_MF_MODE ; 
 int /*<<< orphan*/  NIG_REG_STAT2_BRB_OCTET ; 
 int PBF_REG_HDRS_AFTER_BASIC ; 
 int PBF_REG_HDRS_AFTER_TAG_0 ; 
 int PBF_REG_MUST_HAVE_HDRS ; 
 int PBF_REG_TAG_ETHERTYPE_0 ; 
 int PBF_REG_TAG_LEN_0 ; 
 int PCICFG_OFFSET ; 
 int PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int /*<<< orphan*/  PHASE_COMMON ; 
 int PRS_REG_A_PRSU_20 ; 
 int PRS_REG_E1HOV_MODE ; 
 int PRS_REG_HDRS_AFTER_BASIC ; 
 int PRS_REG_HDRS_AFTER_TAG_0 ; 
 int PRS_REG_MUST_HAVE_HDRS ; 
 int PRS_REG_TAG_ETHERTYPE_0 ; 
 int PRS_REG_TAG_LEN_0 ; 
 int PXP2_REG_PGL_TAGS_LIMIT ; 
 int /*<<< orphan*/  PXP2_REG_PXP2_INT_STS_CLR_0 ; 
 int PXP2_REG_RD_DISABLE_INPUTS ; 
 int /*<<< orphan*/  PXP2_REG_RD_INIT_DONE ; 
 int /*<<< orphan*/  PXP2_REG_RQ_CFG_DONE ; 
 int PXP2_REG_RQ_DISABLE_INPUTS ; 
 int PXP2_REG_RQ_DRAM_ALIGN ; 
 int PXP2_REG_RQ_DRAM_ALIGN_RD ; 
 int PXP2_REG_RQ_DRAM_ALIGN_SEL ; 
 int PXPCS_TL_CONTROL_5 ; 
 int PXPCS_TL_CONTROL_5_ERR_UNSPPORT ; 
 int PXPCS_TL_CONTROL_5_ERR_UNSPPORT1 ; 
 int PXPCS_TL_FUNC345_STAT ; 
 int PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2 ; 
 int PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3 ; 
 int PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4 ; 
 int PXPCS_TL_FUNC678_STAT ; 
 int PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5 ; 
 int PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6 ; 
 int PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7 ; 
 int PXP_REG_PXP_INT_MASK_0 ; 
 int QM_REG_SOFT_RESET ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int SRC_REG_KEYSEARCH_0 ; 
 int SRC_REG_KEYSEARCH_1 ; 
 int SRC_REG_KEYSEARCH_2 ; 
 int SRC_REG_KEYSEARCH_3 ; 
 int SRC_REG_KEYSEARCH_4 ; 
 int SRC_REG_KEYSEARCH_5 ; 
 int SRC_REG_KEYSEARCH_6 ; 
 int SRC_REG_KEYSEARCH_7 ; 
 int SRC_REG_KEYSEARCH_8 ; 
 int SRC_REG_KEYSEARCH_9 ; 
 int SRC_REG_SOFT_RST ; 
 int TSEM_REG_FAST_MEMORY ; 
 int /*<<< orphan*/  TSEM_REG_PASSIVE_BUFFER ; 
 int /*<<< orphan*/  TSEM_REG_PRAM ; 
 int /*<<< orphan*/  USEM_REG_PASSIVE_BUFFER ; 
 int VFC_MEMORIES_RST_REG_CAM_RST ; 
 int VFC_MEMORIES_RST_REG_RAM_RST ; 
 int VFC_REG_MEMORIES_RST ; 
 int XSEM_REG_FAST_MEMORY ; 
 int /*<<< orphan*/  XSEM_REG_PASSIVE_BUFFER ; 
 int /*<<< orphan*/  XSEM_REG_PRAM ; 
 int /*<<< orphan*/  bnx2x__common_init_phy (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_enable_blocks_attention (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_enable_blocks_parity (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_ilt_client_init_op_ilt (struct bnx2x*,struct ilt_client_info*,struct ilt_client_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_ilt_init_page_size (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_block (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_fill (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bnx2x_init_pxp (struct bnx2x*) ; 
 scalar_t__ bnx2x_int_mem_test (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_iov_init_dmae (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_pf_disable (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_pretend_func (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_qm_init_ptr_table (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_read_dmae (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_reset_common (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_set_endianity (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_setup_fan_failure_detection (struct bnx2x*) ; 
 int* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  memset (struct ilt_client_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netproc_fw_ver ; 
 int reg_poll (struct bnx2x*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * wb_data ; 

__attribute__((used)) static int bnx2x_init_hw_common(struct bnx2x *bp)
{
	u32 val;

	DP(NETIF_MSG_HW, "starting common init  func %d\n", BP_ABS_FUNC(bp));

	/*
	 * take the RESET lock to protect undi_unload flow from accessing
	 * registers while we're resetting the chip
	 */
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

	bnx2x_reset_common(bp);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0xffffffff);

	val = 0xfffc;
	if (CHIP_IS_E3(bp)) {
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT0;
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT1;
	}
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET, val);

	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

	bnx2x_init_block(bp, BLOCK_MISC, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp)) {
		u8 abs_func_id;

		/**
		 * 4-port mode or 2-port mode we need to turn of master-enable
		 * for everyone, after that, turn it back on for self.
		 * so, we disregard multi-function or not, and always disable
		 * for all functions on the given path, this means 0,2,4,6 for
		 * path 0 and 1,3,5,7 for path 1
		 */
		for (abs_func_id = BP_PATH(bp);
		     abs_func_id < E2_FUNC_MAX*2; abs_func_id += 2) {
			if (abs_func_id == BP_ABS_FUNC(bp)) {
				REG_WR(bp,
				    PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER,
				    1);
				continue;
			}

			bnx2x_pretend_func(bp, abs_func_id);
			/* clear pf enable */
			bnx2x_pf_disable(bp);
			bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
		}
	}

	bnx2x_init_block(bp, BLOCK_PXP, PHASE_COMMON);
	if (CHIP_IS_E1(bp)) {
		/* enable HW interrupt from PXP on USDM overflow
		   bit 16 on INT_MASK_0 */
		REG_WR(bp, PXP_REG_PXP_INT_MASK_0, 0);
	}

	bnx2x_init_block(bp, BLOCK_PXP2, PHASE_COMMON);
	bnx2x_init_pxp(bp);
	bnx2x_set_endianity(bp);
	bnx2x_ilt_init_page_size(bp, INITOP_SET);

	if (CHIP_REV_IS_FPGA(bp) && CHIP_IS_E1H(bp))
		REG_WR(bp, PXP2_REG_PGL_TAGS_LIMIT, 0x1);

	/* let the HW do it's magic ... */
	msleep(100);
	/* finish PXP init */
	val = REG_RD(bp, PXP2_REG_RQ_CFG_DONE);
	if (val != 1) {
		BNX2X_ERR("PXP2 CFG failed\n");
		return -EBUSY;
	}
	val = REG_RD(bp, PXP2_REG_RD_INIT_DONE);
	if (val != 1) {
		BNX2X_ERR("PXP2 RD_INIT failed\n");
		return -EBUSY;
	}

	/* Timers bug workaround E2 only. We need to set the entire ILT to
	 * have entries with value "0" and valid bit on.
	 * This needs to be done by the first PF that is loaded in a path
	 * (i.e. common phase)
	 */
	if (!CHIP_IS_E1x(bp)) {
/* In E2 there is a bug in the timers block that can cause function 6 / 7
 * (i.e. vnic3) to start even if it is marked as "scan-off".
 * This occurs when a different function (func2,3) is being marked
 * as "scan-off". Real-life scenario for example: if a driver is being
 * load-unloaded while func6,7 are down. This will cause the timer to access
 * the ilt, translate to a logical address and send a request to read/write.
 * Since the ilt for the function that is down is not valid, this will cause
 * a translation error which is unrecoverable.
 * The Workaround is intended to make sure that when this happens nothing fatal
 * will occur. The workaround:
 *	1.  First PF driver which loads on a path will:
 *		a.  After taking the chip out of reset, by using pretend,
 *		    it will write "0" to the following registers of
 *		    the other vnics.
 *		    REG_WR(pdev, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);
 *		    REG_WR(pdev, CFC_REG_WEAK_ENABLE_PF,0);
 *		    REG_WR(pdev, CFC_REG_STRONG_ENABLE_PF,0);
 *		    And for itself it will write '1' to
 *		    PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER to enable
 *		    dmae-operations (writing to pram for example.)
 *		    note: can be done for only function 6,7 but cleaner this
 *			  way.
 *		b.  Write zero+valid to the entire ILT.
 *		c.  Init the first_timers_ilt_entry, last_timers_ilt_entry of
 *		    VNIC3 (of that port). The range allocated will be the
 *		    entire ILT. This is needed to prevent  ILT range error.
 *	2.  Any PF driver load flow:
 *		a.  ILT update with the physical addresses of the allocated
 *		    logical pages.
 *		b.  Wait 20msec. - note that this timeout is needed to make
 *		    sure there are no requests in one of the PXP internal
 *		    queues with "old" ILT addresses.
 *		c.  PF enable in the PGLC.
 *		d.  Clear the was_error of the PF in the PGLC. (could have
 *		    occurred while driver was down)
 *		e.  PF enable in the CFC (WEAK + STRONG)
 *		f.  Timers scan enable
 *	3.  PF driver unload flow:
 *		a.  Clear the Timers scan_en.
 *		b.  Polling for scan_on=0 for that PF.
 *		c.  Clear the PF enable bit in the PXP.
 *		d.  Clear the PF enable in the CFC (WEAK + STRONG)
 *		e.  Write zero+valid to all ILT entries (The valid bit must
 *		    stay set)
 *		f.  If this is VNIC 3 of a port then also init
 *		    first_timers_ilt_entry to zero and last_timers_ilt_entry
 *		    to the last entry in the ILT.
 *
 *	Notes:
 *	Currently the PF error in the PGLC is non recoverable.
 *	In the future the there will be a recovery routine for this error.
 *	Currently attention is masked.
 *	Having an MCP lock on the load/unload process does not guarantee that
 *	there is no Timer disable during Func6/7 enable. This is because the
 *	Timers scan is currently being cleared by the MCP on FLR.
 *	Step 2.d can be done only for PF6/7 and the driver can also check if
 *	there is error before clearing it. But the flow above is simpler and
 *	more general.
 *	All ILT entries are written by zero+valid and not just PF6/7
 *	ILT entries since in the future the ILT entries allocation for
 *	PF-s might be dynamic.
 */
		struct ilt_client_info ilt_cli;
		struct bnx2x_ilt ilt;
		memset(&ilt_cli, 0, sizeof(struct ilt_client_info));
		memset(&ilt, 0, sizeof(struct bnx2x_ilt));

		/* initialize dummy TM client */
		ilt_cli.start = 0;
		ilt_cli.end = ILT_NUM_PAGE_ENTRIES - 1;
		ilt_cli.client_num = ILT_CLIENT_TM;

		/* Step 1: set zeroes to all ilt page entries with valid bit on
		 * Step 2: set the timers first/last ilt entry to point
		 * to the entire range to prevent ILT range error for 3rd/4th
		 * vnic	(this code assumes existence of the vnic)
		 *
		 * both steps performed by call to bnx2x_ilt_client_init_op()
		 * with dummy TM client
		 *
		 * we must use pretend since PXP2_REG_RQ_##blk##_FIRST_ILT
		 * and his brother are split registers
		 */
		bnx2x_pretend_func(bp, (BP_PATH(bp) + 6));
		bnx2x_ilt_client_init_op_ilt(bp, &ilt, &ilt_cli, INITOP_CLEAR);
		bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN, BNX2X_PXP_DRAM_ALIGN);
		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN_RD, BNX2X_PXP_DRAM_ALIGN);
		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN_SEL, 1);
	}

	REG_WR(bp, PXP2_REG_RQ_DISABLE_INPUTS, 0);
	REG_WR(bp, PXP2_REG_RD_DISABLE_INPUTS, 0);

	if (!CHIP_IS_E1x(bp)) {
		int factor = CHIP_REV_IS_EMUL(bp) ? 1000 :
				(CHIP_REV_IS_FPGA(bp) ? 400 : 0);
		bnx2x_init_block(bp, BLOCK_PGLUE_B, PHASE_COMMON);

		bnx2x_init_block(bp, BLOCK_ATC, PHASE_COMMON);

		/* let the HW do it's magic ... */
		do {
			msleep(200);
			val = REG_RD(bp, ATC_REG_ATC_INIT_DONE);
		} while (factor-- && (val != 1));

		if (val != 1) {
			BNX2X_ERR("ATC_INIT failed\n");
			return -EBUSY;
		}
	}

	bnx2x_init_block(bp, BLOCK_DMAE, PHASE_COMMON);

	bnx2x_iov_init_dmae(bp);

	/* clean the DMAE memory */
	bp->dmae_ready = 1;
	bnx2x_init_fill(bp, TSEM_REG_PRAM, 0, 8, 1);

	bnx2x_init_block(bp, BLOCK_TCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_UCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_CCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_XCM, PHASE_COMMON);

	bnx2x_read_dmae(bp, XSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_read_dmae(bp, CSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_read_dmae(bp, TSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_read_dmae(bp, USEM_REG_PASSIVE_BUFFER, 3);

	bnx2x_init_block(bp, BLOCK_QM, PHASE_COMMON);

	/* QM queues pointers table */
	bnx2x_qm_init_ptr_table(bp, bp->qm_cid_count, INITOP_SET);

	/* soft reset pulse */
	REG_WR(bp, QM_REG_SOFT_RESET, 1);
	REG_WR(bp, QM_REG_SOFT_RESET, 0);

	if (CNIC_SUPPORT(bp))
		bnx2x_init_block(bp, BLOCK_TM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_DORQ, PHASE_COMMON);

	if (!CHIP_REV_IS_SLOW(bp))
		/* enable hw interrupt from doorbell Q */
		REG_WR(bp, DORQ_REG_DORQ_INT_MASK, 0);

	bnx2x_init_block(bp, BLOCK_BRB1, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_PRS, PHASE_COMMON);
	REG_WR(bp, PRS_REG_A_PRSU_20, 0xf);

	if (!CHIP_IS_E1(bp))
		REG_WR(bp, PRS_REG_E1HOV_MODE, bp->path_has_ovlan);

	if (!CHIP_IS_E1x(bp) && !CHIP_IS_E3B0(bp)) {
		if (IS_MF_AFEX(bp)) {
			/* configure that VNTag and VLAN headers must be
			 * received in afex mode
			 */
			REG_WR(bp, PRS_REG_HDRS_AFTER_BASIC, 0xE);
			REG_WR(bp, PRS_REG_MUST_HAVE_HDRS, 0xA);
			REG_WR(bp, PRS_REG_HDRS_AFTER_TAG_0, 0x6);
			REG_WR(bp, PRS_REG_TAG_ETHERTYPE_0, 0x8926);
			REG_WR(bp, PRS_REG_TAG_LEN_0, 0x4);
		} else {
			/* Bit-map indicating which L2 hdrs may appear
			 * after the basic Ethernet header
			 */
			REG_WR(bp, PRS_REG_HDRS_AFTER_BASIC,
			       bp->path_has_ovlan ? 7 : 6);
		}
	}

	bnx2x_init_block(bp, BLOCK_TSDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_CSDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_USDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XSDM, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp)) {
		/* reset VFC memories */
		REG_WR(bp, TSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
			   VFC_MEMORIES_RST_REG_CAM_RST |
			   VFC_MEMORIES_RST_REG_RAM_RST);
		REG_WR(bp, XSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
			   VFC_MEMORIES_RST_REG_CAM_RST |
			   VFC_MEMORIES_RST_REG_RAM_RST);

		msleep(20);
	}

	bnx2x_init_block(bp, BLOCK_TSEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_USEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_CSEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XSEM, PHASE_COMMON);

	/* sync semi rtc */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR,
	       0x80000000);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET,
	       0x80000000);

	bnx2x_init_block(bp, BLOCK_UPB, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XPB, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_PBF, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp)) {
		if (IS_MF_AFEX(bp)) {
			/* configure that VNTag and VLAN headers must be
			 * sent in afex mode
			 */
			REG_WR(bp, PBF_REG_HDRS_AFTER_BASIC, 0xE);
			REG_WR(bp, PBF_REG_MUST_HAVE_HDRS, 0xA);
			REG_WR(bp, PBF_REG_HDRS_AFTER_TAG_0, 0x6);
			REG_WR(bp, PBF_REG_TAG_ETHERTYPE_0, 0x8926);
			REG_WR(bp, PBF_REG_TAG_LEN_0, 0x4);
		} else {
			REG_WR(bp, PBF_REG_HDRS_AFTER_BASIC,
			       bp->path_has_ovlan ? 7 : 6);
		}
	}

	REG_WR(bp, SRC_REG_SOFT_RST, 1);

	bnx2x_init_block(bp, BLOCK_SRC, PHASE_COMMON);

	if (CNIC_SUPPORT(bp)) {
		REG_WR(bp, SRC_REG_KEYSEARCH_0, 0x63285672);
		REG_WR(bp, SRC_REG_KEYSEARCH_1, 0x24b8f2cc);
		REG_WR(bp, SRC_REG_KEYSEARCH_2, 0x223aef9b);
		REG_WR(bp, SRC_REG_KEYSEARCH_3, 0x26001e3a);
		REG_WR(bp, SRC_REG_KEYSEARCH_4, 0x7ae91116);
		REG_WR(bp, SRC_REG_KEYSEARCH_5, 0x5ce5230b);
		REG_WR(bp, SRC_REG_KEYSEARCH_6, 0x298d8adf);
		REG_WR(bp, SRC_REG_KEYSEARCH_7, 0x6eb0ff09);
		REG_WR(bp, SRC_REG_KEYSEARCH_8, 0x1830f82f);
		REG_WR(bp, SRC_REG_KEYSEARCH_9, 0x01e46be7);
	}
	REG_WR(bp, SRC_REG_SOFT_RST, 0);

	if (sizeof(union cdu_context) != 1024)
		/* we currently assume that a context is 1024 bytes */
		dev_alert(&bp->pdev->dev,
			  "please adjust the size of cdu_context(%ld)\n",
			  (long)sizeof(union cdu_context));

	bnx2x_init_block(bp, BLOCK_CDU, PHASE_COMMON);
	val = (4 << 24) + (0 << 12) + 1024;
	REG_WR(bp, CDU_REG_CDU_GLOBAL_PARAMS, val);

	bnx2x_init_block(bp, BLOCK_CFC, PHASE_COMMON);
	REG_WR(bp, CFC_REG_INIT_REG, 0x7FF);
	/* enable context validation interrupt from CFC */
	REG_WR(bp, CFC_REG_CFC_INT_MASK, 0);

	/* set the thresholds to prevent CFC/CDU race */
	REG_WR(bp, CFC_REG_DEBUG0, 0x20020000);

	bnx2x_init_block(bp, BLOCK_HC, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp) && BP_NOMCP(bp))
		REG_WR(bp, IGU_REG_RESET_MEMORIES, 0x36);

	bnx2x_init_block(bp, BLOCK_IGU, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_MISC_AEU, PHASE_COMMON);

	/* Reset PCIE errors for debug */
	REG_WR(bp, 0x2814, 0xffffffff);
	REG_WR(bp, 0x3820, 0xffffffff);

	if (!CHIP_IS_E1x(bp)) {
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_CONTROL_5,
			   (PXPCS_TL_CONTROL_5_ERR_UNSPPORT1 |
				PXPCS_TL_CONTROL_5_ERR_UNSPPORT));
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_FUNC345_STAT,
			   (PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4 |
				PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3 |
				PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2));
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_FUNC678_STAT,
			   (PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7 |
				PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6 |
				PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5));
	}

	bnx2x_init_block(bp, BLOCK_NIG, PHASE_COMMON);
	if (!CHIP_IS_E1(bp)) {
		/* in E3 this done in per-port section */
		if (!CHIP_IS_E3(bp))
			REG_WR(bp, NIG_REG_LLH_MF_MODE, IS_MF(bp));
	}
	if (CHIP_IS_E1H(bp))
		/* not applicable for E2 (and above ...) */
		REG_WR(bp, NIG_REG_LLH_E1HOV_MODE, IS_MF_SD(bp));

	if (CHIP_REV_IS_SLOW(bp))
		msleep(200);

	/* finish CFC init */
	val = reg_poll(bp, CFC_REG_LL_INIT_DONE, 1, 100, 10);
	if (val != 1) {
		BNX2X_ERR("CFC LL_INIT failed\n");
		return -EBUSY;
	}
	val = reg_poll(bp, CFC_REG_AC_INIT_DONE, 1, 100, 10);
	if (val != 1) {
		BNX2X_ERR("CFC AC_INIT failed\n");
		return -EBUSY;
	}
	val = reg_poll(bp, CFC_REG_CAM_INIT_DONE, 1, 100, 10);
	if (val != 1) {
		BNX2X_ERR("CFC CAM_INIT failed\n");
		return -EBUSY;
	}
	REG_WR(bp, CFC_REG_DEBUG0, 0);

	if (CHIP_IS_E1(bp)) {
		/* read NIG statistic
		   to see if this is our first up since powerup */
		bnx2x_read_dmae(bp, NIG_REG_STAT2_BRB_OCTET, 2);
		val = *bnx2x_sp(bp, wb_data[0]);

		/* do internal memory self test */
		if ((val == 0) && bnx2x_int_mem_test(bp)) {
			BNX2X_ERR("internal mem self test failed\n");
			return -EBUSY;
		}
	}

	bnx2x_setup_fan_failure_detection(bp);

	/* clear PXP2 attentions */
	REG_RD(bp, PXP2_REG_PXP2_INT_STS_CLR_0);

	bnx2x_enable_blocks_attention(bp);
	bnx2x_enable_blocks_parity(bp);

	if (!BP_NOMCP(bp)) {
		if (CHIP_IS_E1x(bp))
			bnx2x__common_init_phy(bp);
	} else
		BNX2X_ERR("Bootcode is missing - can not initialize link\n");

	if (SHMEM2_HAS(bp, netproc_fw_ver))
		SHMEM2_WR(bp, netproc_fw_ver, REG_RD(bp, XSEM_REG_PRAM));

	return 0;
}