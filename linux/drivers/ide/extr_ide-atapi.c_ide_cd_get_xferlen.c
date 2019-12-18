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
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  ATA_PRIV_PC 133 
#define  ATA_PRIV_SENSE 132 
#define  REQ_OP_DRV_IN 131 
#define  REQ_OP_DRV_OUT 130 
#define  REQ_OP_SCSI_IN 129 
#define  REQ_OP_SCSI_OUT 128 
 int blk_rq_bytes (struct request*) ; 
 TYPE_1__* ide_req (struct request*) ; 
 int req_op (struct request*) ; 

int ide_cd_get_xferlen(struct request *rq)
{
	switch (req_op(rq)) {
	default:
		return 32768;
	case REQ_OP_SCSI_IN:
	case REQ_OP_SCSI_OUT:
		return blk_rq_bytes(rq);
	case REQ_OP_DRV_IN:
	case REQ_OP_DRV_OUT:
		switch (ide_req(rq)->type) {
		case ATA_PRIV_PC:
		case ATA_PRIV_SENSE:
			return blk_rq_bytes(rq);
		default:
			return 0;
		}
	}
}