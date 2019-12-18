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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  vp_idx; struct qla_hw_data* hw; } ;
struct scsi_lun {int dummy; } ;
struct req_que {int /*<<< orphan*/  id; } ;
struct qla_qpair {struct req_que* req; } ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
struct mrk_entry_24xx {int /*<<< orphan*/  handle; int /*<<< orphan*/  vp_index; int /*<<< orphan*/  lun; void* nport_handle; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_2__ {void* lun; int /*<<< orphan*/  target; scalar_t__ modifier; int /*<<< orphan*/  entry_type; } ;
typedef  TYPE_1__ mrk_entry_t ;

/* Variables and functions */
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  MAKE_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MARKER_TYPE ; 
 scalar_t__ MK_SYNC_ALL ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SET_TARGET_ID (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __qla2x00_alloc_iocbs (struct qla_qpair*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_fcp_swap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  int_to_scsilun (scalar_t__,struct scsi_lun*) ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_start_iocbs (struct scsi_qla_host*,struct req_que*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
__qla2x00_marker(struct scsi_qla_host *vha, struct qla_qpair *qpair,
    uint16_t loop_id, uint64_t lun, uint8_t type)
{
	mrk_entry_t *mrk;
	struct mrk_entry_24xx *mrk24 = NULL;
	struct req_que *req = qpair->req;
	struct qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	mrk = (mrk_entry_t *)__qla2x00_alloc_iocbs(qpair, NULL);
	if (mrk == NULL) {
		ql_log(ql_log_warn, base_vha, 0x3026,
		    "Failed to allocate Marker IOCB.\n");

		return (QLA_FUNCTION_FAILED);
	}

	mrk->entry_type = MARKER_TYPE;
	mrk->modifier = type;
	if (type != MK_SYNC_ALL) {
		if (IS_FWI2_CAPABLE(ha)) {
			mrk24 = (struct mrk_entry_24xx *) mrk;
			mrk24->nport_handle = cpu_to_le16(loop_id);
			int_to_scsilun(lun, (struct scsi_lun *)&mrk24->lun);
			host_to_fcp_swap(mrk24->lun, sizeof(mrk24->lun));
			mrk24->vp_index = vha->vp_idx;
			mrk24->handle = MAKE_HANDLE(req->id, mrk24->handle);
		} else {
			SET_TARGET_ID(ha, mrk->target, loop_id);
			mrk->lun = cpu_to_le16((uint16_t)lun);
		}
	}
	wmb();

	qla2x00_start_iocbs(vha, req);

	return (QLA_SUCCESS);
}