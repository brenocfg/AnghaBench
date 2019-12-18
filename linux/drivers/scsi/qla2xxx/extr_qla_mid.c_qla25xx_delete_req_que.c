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
struct TYPE_2__ {scalar_t__ qpairs_req_created; } ;
struct scsi_qla_host {TYPE_1__ flags; } ;
struct req_que {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_0 ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  qla25xx_free_req_que (struct scsi_qla_host*,struct req_que*) ; 
 int qla25xx_init_req_que (struct scsi_qla_host*,struct req_que*) ; 

int
qla25xx_delete_req_que(struct scsi_qla_host *vha, struct req_que *req)
{
	int ret = QLA_SUCCESS;

	if (req && vha->flags.qpairs_req_created) {
		req->options |= BIT_0;
		ret = qla25xx_init_req_que(vha, req);
		if (ret != QLA_SUCCESS)
			return QLA_FUNCTION_FAILED;

		qla25xx_free_req_que(vha, req);
	}

	return ret;
}