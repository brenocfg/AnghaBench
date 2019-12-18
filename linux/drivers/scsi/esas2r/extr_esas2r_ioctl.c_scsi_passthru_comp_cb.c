#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  residual_length; int /*<<< orphan*/  scsi_stat; } ;
struct TYPE_6__ {TYPE_2__ scsi_rsp; } ;
struct esas2r_request {int req_stat; int /*<<< orphan*/  (* aux_req_cb ) (struct esas2r_adapter*,struct esas2r_request*) ;TYPE_3__ func_rsp; int /*<<< orphan*/  sense_len; scalar_t__ aux_req_cx; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_hba_scsi_pass_thru {scalar_t__ target_id; int /*<<< orphan*/  req_status; int /*<<< orphan*/  residual_length; int /*<<< orphan*/  sense_length; int /*<<< orphan*/  scsi_status; } ;
struct TYPE_4__ {struct atto_hba_scsi_pass_thru scsi_pass_thru; } ;
struct atto_ioctl {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTO_SPT_RS_ABORTED ; 
 int /*<<< orphan*/  ATTO_SPT_RS_BUSY ; 
 int /*<<< orphan*/  ATTO_SPT_RS_BUS_RESET ; 
 int /*<<< orphan*/  ATTO_SPT_RS_DEGRADED ; 
 int /*<<< orphan*/  ATTO_SPT_RS_FAILED ; 
 int /*<<< orphan*/  ATTO_SPT_RS_NO_DEVICE ; 
 int /*<<< orphan*/  ATTO_SPT_RS_NO_LUN ; 
 int /*<<< orphan*/  ATTO_SPT_RS_OVERRUN ; 
 int /*<<< orphan*/  ATTO_SPT_RS_SUCCESS ; 
 int /*<<< orphan*/  ATTO_SPT_RS_TIMEOUT ; 
 int /*<<< orphan*/  ATTO_SPT_RS_UNDERRUN ; 
#define  RS_ABORTED 139 
#define  RS_BUSY 138 
#define  RS_DEGRADED 137 
#define  RS_NO_LUN 136 
#define  RS_OVERRUN 135 
#define  RS_RESET 134 
#define  RS_SCSI_ERROR 133 
#define  RS_SEL 132 
#define  RS_SEL2 131 
#define  RS_SUCCESS 130 
#define  RS_TIMEOUT 129 
#define  RS_UNDERRUN 128 
 scalar_t__ esas2r_targ_db_find_next_present (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct esas2r_adapter*,struct esas2r_request*) ; 

__attribute__((used)) static void scsi_passthru_comp_cb(struct esas2r_adapter *a,
				  struct esas2r_request *rq)
{
	struct atto_ioctl *hi = (struct atto_ioctl *)rq->aux_req_cx;
	struct atto_hba_scsi_pass_thru *spt = &hi->data.scsi_pass_thru;
	u8 sts = ATTO_SPT_RS_FAILED;

	spt->scsi_status = rq->func_rsp.scsi_rsp.scsi_stat;
	spt->sense_length = rq->sense_len;
	spt->residual_length =
		le32_to_cpu(rq->func_rsp.scsi_rsp.residual_length);

	switch (rq->req_stat) {
	case RS_SUCCESS:
	case RS_SCSI_ERROR:
		sts = ATTO_SPT_RS_SUCCESS;
		break;
	case RS_UNDERRUN:
		sts = ATTO_SPT_RS_UNDERRUN;
		break;
	case RS_OVERRUN:
		sts = ATTO_SPT_RS_OVERRUN;
		break;
	case RS_SEL:
	case RS_SEL2:
		sts = ATTO_SPT_RS_NO_DEVICE;
		break;
	case RS_NO_LUN:
		sts = ATTO_SPT_RS_NO_LUN;
		break;
	case RS_TIMEOUT:
		sts = ATTO_SPT_RS_TIMEOUT;
		break;
	case RS_DEGRADED:
		sts = ATTO_SPT_RS_DEGRADED;
		break;
	case RS_BUSY:
		sts = ATTO_SPT_RS_BUSY;
		break;
	case RS_ABORTED:
		sts = ATTO_SPT_RS_ABORTED;
		break;
	case RS_RESET:
		sts = ATTO_SPT_RS_BUS_RESET;
		break;
	}

	spt->req_status = sts;

	/* Update the target ID to the next one present. */
	spt->target_id =
		esas2r_targ_db_find_next_present(a, (u16)spt->target_id);

	/* Done, call the completion callback. */
	(*rq->aux_req_cb)(a, rq);
}