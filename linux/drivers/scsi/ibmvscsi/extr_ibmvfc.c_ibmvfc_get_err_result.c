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
struct TYPE_4__ {scalar_t__ rsp_code; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct ibmvfc_fcp_rsp {int flags; int scsi_status; TYPE_2__ data; int /*<<< orphan*/  fcp_rsp_len; } ;
struct ibmvfc_cmd {int /*<<< orphan*/  error; int /*<<< orphan*/  status; struct ibmvfc_fcp_rsp rsp; } ;
struct TYPE_6__ {int result; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int FCP_RSP_LEN_VALID ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__* cmd_status ; 
 int ibmvfc_get_err_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_get_err_result(struct ibmvfc_cmd *vfc_cmd)
{
	int err;
	struct ibmvfc_fcp_rsp *rsp = &vfc_cmd->rsp;
	int fc_rsp_len = be32_to_cpu(rsp->fcp_rsp_len);

	if ((rsp->flags & FCP_RSP_LEN_VALID) &&
	    ((fc_rsp_len && fc_rsp_len != 4 && fc_rsp_len != 8) ||
	     rsp->data.info.rsp_code))
		return DID_ERROR << 16;

	err = ibmvfc_get_err_index(be16_to_cpu(vfc_cmd->status), be16_to_cpu(vfc_cmd->error));
	if (err >= 0)
		return rsp->scsi_status | (cmd_status[err].result << 16);
	return rsp->scsi_status | (DID_ERROR << 16);
}