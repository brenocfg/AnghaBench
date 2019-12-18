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
struct fw_iq_cmd {int /*<<< orphan*/  fl0addr; int /*<<< orphan*/  fl0size; int /*<<< orphan*/  fl0dcaen_to_fl0cidxfthresh; int /*<<< orphan*/  iqns_to_fl0congen; int /*<<< orphan*/  iqaddr; int /*<<< orphan*/  iqsize; int /*<<< orphan*/  iqdroprss_to_iqesize; int /*<<< orphan*/  type_to_iqandstindex; int /*<<< orphan*/  fl1id; int /*<<< orphan*/  fl0id; int /*<<< orphan*/  iqid; int /*<<< orphan*/  alloc_to_len16; int /*<<< orphan*/  op_to_vfn; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_iq_params {int iqid; int fl0id; int fl1id; int iqsize; scalar_t__ type; int fl0size; scalar_t__ fl0addr; int /*<<< orphan*/  fl0cidxfthresh; int /*<<< orphan*/  fl0fbmax; int /*<<< orphan*/  fl0fbmin; int /*<<< orphan*/  fl0dcacpu; int /*<<< orphan*/  fl0dcaen; int /*<<< orphan*/  fl0packen; int /*<<< orphan*/  fl0paden; int /*<<< orphan*/  fl0cprio; int /*<<< orphan*/  fl0hostfcmode; int /*<<< orphan*/  iqflintcongen; int /*<<< orphan*/  iqflintiqhsen; scalar_t__ iqaddr; int /*<<< orphan*/  iqesize; int /*<<< orphan*/  iqcprio; int /*<<< orphan*/  iqintcntthresh; int /*<<< orphan*/  iqdcacpu; int /*<<< orphan*/  iqdcaen; int /*<<< orphan*/  iqpciech; int /*<<< orphan*/  iqandstindex; int /*<<< orphan*/  iqanud; int /*<<< orphan*/  iqanus; int /*<<< orphan*/  iqandst; int /*<<< orphan*/  vfn; int /*<<< orphan*/  pfn; scalar_t__ iq_start; } ;
struct csio_hw {int flags; } ;

/* Variables and functions */
 int CSIO_HWF_ROOT_NO_RELAXED_ORDERING ; 
 int /*<<< orphan*/  CSIO_INIT_MBP (struct csio_mb*,struct fw_iq_cmd*,int,void*,void (*) (struct csio_hw*,struct csio_mb*),int) ; 
 int FW_CMD_LEN16_V (int) ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_IQ_CMD ; 
 int FW_IQ_CMD_FL0CIDXFTHRESH_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0CPRIO_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0DATARO_V (int) ; 
 int FW_IQ_CMD_FL0DCACPU_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0DCAEN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0FBMAX_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0FBMIN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0FETCHRO_V (int) ; 
 int FW_IQ_CMD_FL0HOSTFCMODE_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0PACKEN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_FL0PADEN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQANDSTINDEX_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQANDST_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQANUD_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQANUS_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQCPRIO_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQDCACPU_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQDCAEN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQESIZE_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQFLINTCONGEN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQFLINTIQHSEN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQINTCNTTHRESH_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQPCIECH_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_IQSTART_F ; 
 int FW_IQ_CMD_IQSTOP_F ; 
 int FW_IQ_CMD_PFN_V (int /*<<< orphan*/ ) ; 
 int FW_IQ_CMD_VFN_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void
csio_mb_iq_write(struct csio_hw *hw, struct csio_mb *mbp, void *priv,
		 uint32_t mb_tmo, bool cascaded_req,
		 struct csio_iq_params *iq_params,
		 void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct fw_iq_cmd *cmdp = (struct fw_iq_cmd *)(mbp->mb);

	uint32_t iq_start_stop = (iq_params->iq_start)	?
					FW_IQ_CMD_IQSTART_F :
					FW_IQ_CMD_IQSTOP_F;
	int relaxed = !(hw->flags & CSIO_HWF_ROOT_NO_RELAXED_ORDERING);

	/*
	 * If this IQ write is cascaded with IQ alloc request, do not
	 * re-initialize with 0's.
	 *
	 */
	if (!cascaded_req)
		CSIO_INIT_MBP(mbp, cmdp, mb_tmo, priv, cbfn, 1);

	cmdp->op_to_vfn |= htonl(FW_CMD_OP_V(FW_IQ_CMD)		|
				FW_CMD_REQUEST_F | FW_CMD_WRITE_F	|
				FW_IQ_CMD_PFN_V(iq_params->pfn)	|
				FW_IQ_CMD_VFN_V(iq_params->vfn));
	cmdp->alloc_to_len16 |= htonl(iq_start_stop |
				FW_CMD_LEN16_V(sizeof(*cmdp) / 16));
	cmdp->iqid |= htons(iq_params->iqid);
	cmdp->fl0id |= htons(iq_params->fl0id);
	cmdp->fl1id |= htons(iq_params->fl1id);
	cmdp->type_to_iqandstindex |= htonl(
			FW_IQ_CMD_IQANDST_V(iq_params->iqandst)	|
			FW_IQ_CMD_IQANUS_V(iq_params->iqanus)	|
			FW_IQ_CMD_IQANUD_V(iq_params->iqanud)	|
			FW_IQ_CMD_IQANDSTINDEX_V(iq_params->iqandstindex));
	cmdp->iqdroprss_to_iqesize |= htons(
			FW_IQ_CMD_IQPCIECH_V(iq_params->iqpciech)	|
			FW_IQ_CMD_IQDCAEN_V(iq_params->iqdcaen)		|
			FW_IQ_CMD_IQDCACPU_V(iq_params->iqdcacpu)	|
			FW_IQ_CMD_IQINTCNTTHRESH_V(iq_params->iqintcntthresh) |
			FW_IQ_CMD_IQCPRIO_V(iq_params->iqcprio)		|
			FW_IQ_CMD_IQESIZE_V(iq_params->iqesize));

	cmdp->iqsize |= htons(iq_params->iqsize);
	cmdp->iqaddr |= cpu_to_be64(iq_params->iqaddr);

	if (iq_params->type == 0) {
		cmdp->iqns_to_fl0congen |= htonl(
			FW_IQ_CMD_IQFLINTIQHSEN_V(iq_params->iqflintiqhsen)|
			FW_IQ_CMD_IQFLINTCONGEN_V(iq_params->iqflintcongen));
	}

	if (iq_params->fl0size && iq_params->fl0addr &&
	    (iq_params->fl0id != 0xFFFF)) {

		cmdp->iqns_to_fl0congen |= htonl(
			FW_IQ_CMD_FL0HOSTFCMODE_V(iq_params->fl0hostfcmode)|
			FW_IQ_CMD_FL0CPRIO_V(iq_params->fl0cprio)	|
			FW_IQ_CMD_FL0FETCHRO_V(relaxed)			|
			FW_IQ_CMD_FL0DATARO_V(relaxed)			|
			FW_IQ_CMD_FL0PADEN_V(iq_params->fl0paden)	|
			FW_IQ_CMD_FL0PACKEN_V(iq_params->fl0packen));
		cmdp->fl0dcaen_to_fl0cidxfthresh |= htons(
			FW_IQ_CMD_FL0DCAEN_V(iq_params->fl0dcaen)	|
			FW_IQ_CMD_FL0DCACPU_V(iq_params->fl0dcacpu)	|
			FW_IQ_CMD_FL0FBMIN_V(iq_params->fl0fbmin)	|
			FW_IQ_CMD_FL0FBMAX_V(iq_params->fl0fbmax)	|
			FW_IQ_CMD_FL0CIDXFTHRESH_V(iq_params->fl0cidxfthresh));
		cmdp->fl0size |= htons(iq_params->fl0size);
		cmdp->fl0addr |= cpu_to_be64(iq_params->fl0addr);
	}
}