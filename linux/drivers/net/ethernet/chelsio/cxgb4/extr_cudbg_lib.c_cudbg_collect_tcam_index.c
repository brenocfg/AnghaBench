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
typedef  int u64 ;
typedef  int u32 ;
struct fw_ldst_mps_rplc {int /*<<< orphan*/  rplc255_224; int /*<<< orphan*/  rplc223_192; int /*<<< orphan*/  rplc191_160; int /*<<< orphan*/  rplc159_128; int /*<<< orphan*/  rplc127_96; int /*<<< orphan*/  rplc95_64; int /*<<< orphan*/  rplc63_32; int /*<<< orphan*/  rplc31_0; int /*<<< orphan*/  fid_idx; } ;
struct TYPE_5__ {struct fw_ldst_mps_rplc rplc; } ;
struct TYPE_6__ {TYPE_1__ mps; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct cudbg_mps_tcam {int vniy; int dip_hit; int vlan_vld; int ivlan; int vnix; int cls_lo; int cls_hi; int repli; int idx; scalar_t__ rplc_size; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; void** rplc; int /*<<< orphan*/  lookup_type; int /*<<< orphan*/  port_num; } ;
struct cudbg_init {struct adapter* adap; } ;
struct TYPE_7__ {scalar_t__ mps_rplc_size; } ;
struct TYPE_8__ {TYPE_3__ arch; int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_4__ params; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  ldst_cmd ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T6 ; 
 int CTLCMDTYPE_V (int /*<<< orphan*/ ) ; 
 int CTLREQID_V (int) ; 
 int CTLTCAMINDEX_V (int) ; 
 int CTLTCAMSEL_V (int) ; 
 int CTLXYBITSEL_V (int) ; 
 scalar_t__ CUDBG_MAX_RPLC_SIZE ; 
 int DATADIPHIT_F ; 
 int /*<<< orphan*/  DATALKPTYPE_G (int) ; 
 int /*<<< orphan*/  DATALKPTYPE_M ; 
 int /*<<< orphan*/  DATAPORTNUM_G (int) ; 
 int DATAVIDH1_G (int) ; 
 int DATAVIDH2_F ; 
 int DMACH_G (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_MPS ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LDST_CMD_ADDRSPACE_V (int /*<<< orphan*/ ) ; 
 int FW_LDST_CMD_FID_V (int /*<<< orphan*/ ) ; 
 int FW_LDST_CMD_IDX_V (int) ; 
 int /*<<< orphan*/  FW_LDST_MPS_RPLC ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 int /*<<< orphan*/  MPS_CLS_SRAM_H (int) ; 
 int /*<<< orphan*/  MPS_CLS_SRAM_L (int) ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_DATA2_CTL_A ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_RDATA0_REQ_ID1_A ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_RDATA1_REQ_ID1_A ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_RDATA2_REQ_ID1_A ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_X_L (int) ; 
 int /*<<< orphan*/  MPS_CLS_TCAM_Y_L (int) ; 
 int REPLICATE_F ; 
 int T6_REPLICATE_F ; 
 int VIDL_G (int) ; 
 int /*<<< orphan*/  cudbg_mps_rpl_backdoor (struct adapter*,struct fw_ldst_mps_rplc*) ; 
 int /*<<< orphan*/  cudbg_tcamxy2valmask (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ is_fw_attached (struct cudbg_init*) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_read_reg64 (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cudbg_collect_tcam_index(struct cudbg_init *pdbg_init,
				    struct cudbg_mps_tcam *tcam, u32 idx)
{
	struct adapter *padap = pdbg_init->adap;
	u64 tcamy, tcamx, val;
	u32 ctl, data2;
	int rc = 0;

	if (CHELSIO_CHIP_VERSION(padap->params.chip) >= CHELSIO_T6) {
		/* CtlReqID   - 1: use Host Driver Requester ID
		 * CtlCmdType - 0: Read, 1: Write
		 * CtlTcamSel - 0: TCAM0, 1: TCAM1
		 * CtlXYBitSel- 0: Y bit, 1: X bit
		 */

		/* Read tcamy */
		ctl = CTLREQID_V(1) | CTLCMDTYPE_V(0) | CTLXYBITSEL_V(0);
		if (idx < 256)
			ctl |= CTLTCAMINDEX_V(idx) | CTLTCAMSEL_V(0);
		else
			ctl |= CTLTCAMINDEX_V(idx - 256) | CTLTCAMSEL_V(1);

		t4_write_reg(padap, MPS_CLS_TCAM_DATA2_CTL_A, ctl);
		val = t4_read_reg(padap, MPS_CLS_TCAM_RDATA1_REQ_ID1_A);
		tcamy = DMACH_G(val) << 32;
		tcamy |= t4_read_reg(padap, MPS_CLS_TCAM_RDATA0_REQ_ID1_A);
		data2 = t4_read_reg(padap, MPS_CLS_TCAM_RDATA2_REQ_ID1_A);
		tcam->lookup_type = DATALKPTYPE_G(data2);

		/* 0 - Outer header, 1 - Inner header
		 * [71:48] bit locations are overloaded for
		 * outer vs. inner lookup types.
		 */
		if (tcam->lookup_type && tcam->lookup_type != DATALKPTYPE_M) {
			/* Inner header VNI */
			tcam->vniy = (data2 & DATAVIDH2_F) | DATAVIDH1_G(data2);
			tcam->vniy = (tcam->vniy << 16) | VIDL_G(val);
			tcam->dip_hit = data2 & DATADIPHIT_F;
		} else {
			tcam->vlan_vld = data2 & DATAVIDH2_F;
			tcam->ivlan = VIDL_G(val);
		}

		tcam->port_num = DATAPORTNUM_G(data2);

		/* Read tcamx. Change the control param */
		ctl |= CTLXYBITSEL_V(1);
		t4_write_reg(padap, MPS_CLS_TCAM_DATA2_CTL_A, ctl);
		val = t4_read_reg(padap, MPS_CLS_TCAM_RDATA1_REQ_ID1_A);
		tcamx = DMACH_G(val) << 32;
		tcamx |= t4_read_reg(padap, MPS_CLS_TCAM_RDATA0_REQ_ID1_A);
		data2 = t4_read_reg(padap, MPS_CLS_TCAM_RDATA2_REQ_ID1_A);
		if (tcam->lookup_type && tcam->lookup_type != DATALKPTYPE_M) {
			/* Inner header VNI mask */
			tcam->vnix = (data2 & DATAVIDH2_F) | DATAVIDH1_G(data2);
			tcam->vnix = (tcam->vnix << 16) | VIDL_G(val);
		}
	} else {
		tcamy = t4_read_reg64(padap, MPS_CLS_TCAM_Y_L(idx));
		tcamx = t4_read_reg64(padap, MPS_CLS_TCAM_X_L(idx));
	}

	/* If no entry, return */
	if (tcamx & tcamy)
		return rc;

	tcam->cls_lo = t4_read_reg(padap, MPS_CLS_SRAM_L(idx));
	tcam->cls_hi = t4_read_reg(padap, MPS_CLS_SRAM_H(idx));

	if (is_t5(padap->params.chip))
		tcam->repli = (tcam->cls_lo & REPLICATE_F);
	else if (is_t6(padap->params.chip))
		tcam->repli = (tcam->cls_lo & T6_REPLICATE_F);

	if (tcam->repli) {
		struct fw_ldst_cmd ldst_cmd;
		struct fw_ldst_mps_rplc mps_rplc;

		memset(&ldst_cmd, 0, sizeof(ldst_cmd));
		ldst_cmd.op_to_addrspace =
			htonl(FW_CMD_OP_V(FW_LDST_CMD) |
			      FW_CMD_REQUEST_F | FW_CMD_READ_F |
			      FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_MPS));
		ldst_cmd.cycles_to_len16 = htonl(FW_LEN16(ldst_cmd));
		ldst_cmd.u.mps.rplc.fid_idx =
			htons(FW_LDST_CMD_FID_V(FW_LDST_MPS_RPLC) |
			      FW_LDST_CMD_IDX_V(idx));

		/* If firmware is not attached/alive, use backdoor register
		 * access to collect dump.
		 */
		if (is_fw_attached(pdbg_init))
			rc = t4_wr_mbox(padap, padap->mbox, &ldst_cmd,
					sizeof(ldst_cmd), &ldst_cmd);

		if (rc || !is_fw_attached(pdbg_init)) {
			cudbg_mps_rpl_backdoor(padap, &mps_rplc);
			/* Ignore error since we collected directly from
			 * reading registers.
			 */
			rc = 0;
		} else {
			mps_rplc = ldst_cmd.u.mps.rplc;
		}

		tcam->rplc[0] = ntohl(mps_rplc.rplc31_0);
		tcam->rplc[1] = ntohl(mps_rplc.rplc63_32);
		tcam->rplc[2] = ntohl(mps_rplc.rplc95_64);
		tcam->rplc[3] = ntohl(mps_rplc.rplc127_96);
		if (padap->params.arch.mps_rplc_size > CUDBG_MAX_RPLC_SIZE) {
			tcam->rplc[4] = ntohl(mps_rplc.rplc159_128);
			tcam->rplc[5] = ntohl(mps_rplc.rplc191_160);
			tcam->rplc[6] = ntohl(mps_rplc.rplc223_192);
			tcam->rplc[7] = ntohl(mps_rplc.rplc255_224);
		}
	}
	cudbg_tcamxy2valmask(tcamx, tcamy, tcam->addr, &tcam->mask);
	tcam->idx = idx;
	tcam->rplc_size = padap->params.arch.mps_rplc_size;
	return rc;
}