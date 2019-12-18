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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_scsi_abrt_cls_wr {uintptr_t cookie; int sub_opcode_to_chk_all_io; uintptr_t t_cookie; scalar_t__* r3; scalar_t__ tmo_val; int /*<<< orphan*/  iqid; void* flowid_len16; void* op_immdlen; } ;
struct csio_rnode {int /*<<< orphan*/  flowid; } ;
struct csio_ioreq {scalar_t__ tmo; int /*<<< orphan*/  iq_idx; struct csio_rnode* rnode; TYPE_1__* lnode; } ;
struct csio_hw {int dummy; } ;
struct TYPE_2__ {struct csio_hw* hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FW_SCSI_ABRT_CLS_WR ; 
 int FW_SCSI_ABRT_CLS_WR_CHK_ALL_IO (int /*<<< orphan*/ ) ; 
 int FW_SCSI_ABRT_CLS_WR_SUB_OPCODE (int) ; 
 int FW_WR_FLOWID_V (int /*<<< orphan*/ ) ; 
 int FW_WR_LEN16_V (int /*<<< orphan*/ ) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  csio_q_physiqid (struct csio_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
csio_scsi_init_abrt_cls_wr(struct csio_ioreq *req, void *addr, uint32_t size,
			   bool abort)
{
	struct csio_hw *hw = req->lnode->hwp;
	struct csio_rnode *rn = req->rnode;
	struct fw_scsi_abrt_cls_wr *wr = (struct fw_scsi_abrt_cls_wr *)addr;

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_SCSI_ABRT_CLS_WR));
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(rn->flowid) |
					    FW_WR_LEN16_V(
						DIV_ROUND_UP(size, 16)));

	wr->cookie = (uintptr_t) req;
	wr->iqid = cpu_to_be16(csio_q_physiqid(hw, req->iq_idx));
	wr->tmo_val = (uint8_t) req->tmo;
	/* 0 for CHK_ALL_IO tells FW to look up t_cookie */
	wr->sub_opcode_to_chk_all_io =
				(FW_SCSI_ABRT_CLS_WR_SUB_OPCODE(abort) |
				 FW_SCSI_ABRT_CLS_WR_CHK_ALL_IO(0));
	wr->r3[0] = 0;
	wr->r3[1] = 0;
	wr->r3[2] = 0;
	wr->r3[3] = 0;
	/* Since we re-use the same ioreq for abort as well */
	wr->t_cookie = (uintptr_t) req;
}