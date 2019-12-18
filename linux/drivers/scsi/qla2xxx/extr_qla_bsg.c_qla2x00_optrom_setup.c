#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {int optrom_size; scalar_t__ optrom_state; int optrom_region_start; int flt_region_boot; int flt_region_fw; scalar_t__ optrom_region_size; int /*<<< orphan*/  optrom_buffer; int /*<<< orphan*/  pdev; } ;
struct TYPE_9__ {int* vendor_cmd; } ;
struct TYPE_10__ {TYPE_1__ h_vendor; } ;
struct fc_bsg_request {TYPE_2__ rqst_data; } ;
struct TYPE_12__ {scalar_t__ payload_len; } ;
struct TYPE_11__ {scalar_t__ payload_len; } ;
struct bsg_job {TYPE_4__ reply_payload; TYPE_3__ request_payload; struct fc_bsg_request* request; } ;
struct TYPE_13__ {struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2031 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA24XX_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA25XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ OPTROM_SIZE_2300 ; 
 scalar_t__ QLA_SREADING ; 
 scalar_t__ QLA_SWAITING ; 
 scalar_t__ QLA_SWRITING ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_5__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_5__*,int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (scalar_t__) ; 

__attribute__((used)) static int
qla2x00_optrom_setup(struct bsg_job *bsg_job, scsi_qla_host_t *vha,
	uint8_t is_update)
{
	struct fc_bsg_request *bsg_request = bsg_job->request;
	uint32_t start = 0;
	int valid = 0;
	struct qla_hw_data *ha = vha->hw;

	if (unlikely(pci_channel_offline(ha->pdev)))
		return -EINVAL;

	start = bsg_request->rqst_data.h_vendor.vendor_cmd[1];
	if (start > ha->optrom_size) {
		ql_log(ql_log_warn, vha, 0x7055,
		    "start %d > optrom_size %d.\n", start, ha->optrom_size);
		return -EINVAL;
	}

	if (ha->optrom_state != QLA_SWAITING) {
		ql_log(ql_log_info, vha, 0x7056,
		    "optrom_state %d.\n", ha->optrom_state);
		return -EBUSY;
	}

	ha->optrom_region_start = start;
	ql_dbg(ql_dbg_user, vha, 0x7057, "is_update=%d.\n", is_update);
	if (is_update) {
		if (ha->optrom_size == OPTROM_SIZE_2300 && start == 0)
			valid = 1;
		else if (start == (ha->flt_region_boot * 4) ||
		    start == (ha->flt_region_fw * 4))
			valid = 1;
		else if (IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha) ||
		    IS_CNA_CAPABLE(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha) ||
		    IS_QLA28XX(ha))
			valid = 1;
		if (!valid) {
			ql_log(ql_log_warn, vha, 0x7058,
			    "Invalid start region 0x%x/0x%x.\n", start,
			    bsg_job->request_payload.payload_len);
			return -EINVAL;
		}

		ha->optrom_region_size = start +
		    bsg_job->request_payload.payload_len > ha->optrom_size ?
		    ha->optrom_size - start :
		    bsg_job->request_payload.payload_len;
		ha->optrom_state = QLA_SWRITING;
	} else {
		ha->optrom_region_size = start +
		    bsg_job->reply_payload.payload_len > ha->optrom_size ?
		    ha->optrom_size - start :
		    bsg_job->reply_payload.payload_len;
		ha->optrom_state = QLA_SREADING;
	}

	ha->optrom_buffer = vzalloc(ha->optrom_region_size);
	if (!ha->optrom_buffer) {
		ql_log(ql_log_warn, vha, 0x7059,
		    "Read: Unable to allocate memory for optrom retrieval "
		    "(%x)\n", ha->optrom_region_size);

		ha->optrom_state = QLA_SWAITING;
		return -ENOMEM;
	}

	return 0;
}