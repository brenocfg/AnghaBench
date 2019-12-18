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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct request {int cmd_flags; } ;
struct nvme_ns {int lba_shift; int pi_type; scalar_t__ ms; TYPE_1__* head; struct nvme_ctrl* ctrl; } ;
struct nvme_ctrl {scalar_t__ nr_streams; } ;
struct TYPE_4__ {void* dsmgmt; void* control; void* reftag; void* length; int /*<<< orphan*/  slba; void* nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_2__ rw; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  ns_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 
#define  NVME_NS_DPS_PI_TYPE1 130 
#define  NVME_NS_DPS_PI_TYPE2 129 
#define  NVME_NS_DPS_PI_TYPE3 128 
 int /*<<< orphan*/  NVME_RW_DSM_FREQ_PREFETCH ; 
 int NVME_RW_FUA ; 
 int NVME_RW_LR ; 
 int NVME_RW_PRINFO_PRACT ; 
 int NVME_RW_PRINFO_PRCHK_GUARD ; 
 int NVME_RW_PRINFO_PRCHK_REF ; 
 int REQ_FAILFAST_DEV ; 
 int REQ_FUA ; 
 scalar_t__ REQ_OP_WRITE ; 
 int REQ_RAHEAD ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_integrity_rq (struct request*) ; 
 int blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_assign_write_stream (struct nvme_ctrl*,struct request*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_block_nr (struct nvme_ns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cmd_read ; 
 int /*<<< orphan*/  nvme_cmd_write ; 
 int /*<<< orphan*/  nvme_ns_has_pi (struct nvme_ns*) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  t10_pi_ref_tag (struct request*) ; 

__attribute__((used)) static inline blk_status_t nvme_setup_rw(struct nvme_ns *ns,
		struct request *req, struct nvme_command *cmnd)
{
	struct nvme_ctrl *ctrl = ns->ctrl;
	u16 control = 0;
	u32 dsmgmt = 0;

	if (req->cmd_flags & REQ_FUA)
		control |= NVME_RW_FUA;
	if (req->cmd_flags & (REQ_FAILFAST_DEV | REQ_RAHEAD))
		control |= NVME_RW_LR;

	if (req->cmd_flags & REQ_RAHEAD)
		dsmgmt |= NVME_RW_DSM_FREQ_PREFETCH;

	cmnd->rw.opcode = (rq_data_dir(req) ? nvme_cmd_write : nvme_cmd_read);
	cmnd->rw.nsid = cpu_to_le32(ns->head->ns_id);
	cmnd->rw.slba = cpu_to_le64(nvme_block_nr(ns, blk_rq_pos(req)));
	cmnd->rw.length = cpu_to_le16((blk_rq_bytes(req) >> ns->lba_shift) - 1);

	if (req_op(req) == REQ_OP_WRITE && ctrl->nr_streams)
		nvme_assign_write_stream(ctrl, req, &control, &dsmgmt);

	if (ns->ms) {
		/*
		 * If formated with metadata, the block layer always provides a
		 * metadata buffer if CONFIG_BLK_DEV_INTEGRITY is enabled.  Else
		 * we enable the PRACT bit for protection information or set the
		 * namespace capacity to zero to prevent any I/O.
		 */
		if (!blk_integrity_rq(req)) {
			if (WARN_ON_ONCE(!nvme_ns_has_pi(ns)))
				return BLK_STS_NOTSUPP;
			control |= NVME_RW_PRINFO_PRACT;
		}

		switch (ns->pi_type) {
		case NVME_NS_DPS_PI_TYPE3:
			control |= NVME_RW_PRINFO_PRCHK_GUARD;
			break;
		case NVME_NS_DPS_PI_TYPE1:
		case NVME_NS_DPS_PI_TYPE2:
			control |= NVME_RW_PRINFO_PRCHK_GUARD |
					NVME_RW_PRINFO_PRCHK_REF;
			cmnd->rw.reftag = cpu_to_le32(t10_pi_ref_tag(req));
			break;
		}
	}

	cmnd->rw.control = cpu_to_le16(control);
	cmnd->rw.dsmgmt = cpu_to_le32(dsmgmt);
	return 0;
}