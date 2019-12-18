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
typedef  int uint32_t ;
struct fw_eq_ofld_cmd {int /*<<< orphan*/  eqaddr; int /*<<< orphan*/  dcaen_to_eqsize; int /*<<< orphan*/  fetchszm_to_iqid; int /*<<< orphan*/  eqid_pkd; int /*<<< orphan*/  alloc_to_len16; int /*<<< orphan*/  op_to_vfn; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;
struct csio_eq_params {int /*<<< orphan*/  eqaddr; int /*<<< orphan*/  eqsize; int /*<<< orphan*/  cidxfthresh; int /*<<< orphan*/  cidxfthresho; int /*<<< orphan*/  fbmax; int /*<<< orphan*/  fbmin; int /*<<< orphan*/  dcacpu; int /*<<< orphan*/  dcaen; int /*<<< orphan*/  iqid; int /*<<< orphan*/  pciechn; int /*<<< orphan*/  cprio; int /*<<< orphan*/  hostfcmode; int /*<<< orphan*/  eqid; int /*<<< orphan*/  vfn; int /*<<< orphan*/  pfn; scalar_t__ eqstart; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_eq_ofld_cmd*,int,void*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_EQ_OFLD_CMD ; 
 int FW_EQ_OFLD_CMD_CIDXFTHRESHO_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_CIDXFTHRESH_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_CPRIO_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_DCACPU_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_DCAEN_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_EQID_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_EQSIZE_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_EQSTART_F ; 
 int FW_EQ_OFLD_CMD_EQSTOP_F ; 
 int FW_EQ_OFLD_CMD_FBMAX_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_FBMIN_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_HOSTFCMODE_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_IQID_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_PCIECHN_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_PFN_V (int /*<<< orphan*/ ) ; 
 int FW_EQ_OFLD_CMD_VFN_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static void
csio_mb_eq_ofld_write(struct csio_hw *hw, struct csio_mb *mbp, void *priv,
		      uint32_t mb_tmo, bool cascaded_req,
		      struct csio_eq_params *eq_ofld_params,
		      void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_eq_ofld_cmd *cmdp = (struct fw_eq_ofld_cmd *)(mbp->mb);

	uint32_t eq_start_stop = (eq_ofld_params->eqstart)	?
				FW_EQ_OFLD_CMD_EQSTART_F :
				FW_EQ_OFLD_CMD_EQSTOP_F;

	/*
	 * If this EQ write is cascaded with EQ alloc request, do not
	 * re-initialize with 0's.
	 *
	 */
	if (!cascaded_req)
		CSIO_INIT_MBP(mbp, cmdp, mb_tmo, priv, cbfn, 1);

	cmdp->op_to_vfn |= htonl(FW_CMD_OP_V(FW_EQ_OFLD_CMD)	|
				FW_CMD_REQUEST_F | FW_CMD_WRITE_F	|
				FW_EQ_OFLD_CMD_PFN_V(eq_ofld_params->pfn) |
				FW_EQ_OFLD_CMD_VFN_V(eq_ofld_params->vfn));
	cmdp->alloc_to_len16 |= htonl(eq_start_stop		|
				      FW_CMD_LEN16_V(sizeof(*cmdp) / 16));

	cmdp->eqid_pkd |= htonl(FW_EQ_OFLD_CMD_EQID_V(eq_ofld_params->eqid));

	cmdp->fetchszm_to_iqid |= htonl(
		FW_EQ_OFLD_CMD_HOSTFCMODE_V(eq_ofld_params->hostfcmode)	|
		FW_EQ_OFLD_CMD_CPRIO_V(eq_ofld_params->cprio)		|
		FW_EQ_OFLD_CMD_PCIECHN_V(eq_ofld_params->pciechn)	|
		FW_EQ_OFLD_CMD_IQID_V(eq_ofld_params->iqid));

	cmdp->dcaen_to_eqsize |= htonl(
		FW_EQ_OFLD_CMD_DCAEN_V(eq_ofld_params->dcaen)		|
		FW_EQ_OFLD_CMD_DCACPU_V(eq_ofld_params->dcacpu)		|
		FW_EQ_OFLD_CMD_FBMIN_V(eq_ofld_params->fbmin)		|
		FW_EQ_OFLD_CMD_FBMAX_V(eq_ofld_params->fbmax)		|
		FW_EQ_OFLD_CMD_CIDXFTHRESHO_V(eq_ofld_params->cidxfthresho) |
		FW_EQ_OFLD_CMD_CIDXFTHRESH_V(eq_ofld_params->cidxfthresh) |
		FW_EQ_OFLD_CMD_EQSIZE_V(eq_ofld_params->eqsize));

	cmdp->eqaddr |= cpu_to_be64(eq_ofld_params->eqaddr);

}