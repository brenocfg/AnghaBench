#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct kwqe {int dummy; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  op_code; } ;
struct fcoe_kwqe_stat {void* stat_params_addr_hi; void* stat_params_addr_lo; TYPE_1__ hdr; } ;
struct bnx2fc_hba {TYPE_2__* cnic; scalar_t__ stats_buf_dma; } ;
struct TYPE_4__ {int (* submit_kwqes ) (TYPE_2__*,struct kwqe**,int) ;} ;

/* Variables and functions */
 int FCOE_KWQE_HEADER_LAYER_CODE_SHIFT ; 
 int FCOE_KWQE_LAYER_CODE ; 
 int /*<<< orphan*/  FCOE_KWQE_OPCODE_STAT ; 
 int /*<<< orphan*/  memset (struct fcoe_kwqe_stat*,int,int) ; 
 int stub1 (TYPE_2__*,struct kwqe**,int) ; 

int bnx2fc_send_stat_req(struct bnx2fc_hba *hba)
{
	struct fcoe_kwqe_stat stat_req;
	struct kwqe *kwqe_arr[2];
	int num_kwqes = 1;
	int rc = 0;

	memset(&stat_req, 0x00, sizeof(struct fcoe_kwqe_stat));
	stat_req.hdr.op_code = FCOE_KWQE_OPCODE_STAT;
	stat_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	stat_req.stat_params_addr_lo = (u32) hba->stats_buf_dma;
	stat_req.stat_params_addr_hi = (u32) ((u64)hba->stats_buf_dma >> 32);

	kwqe_arr[0] = (struct kwqe *) &stat_req;

	if (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	return rc;
}