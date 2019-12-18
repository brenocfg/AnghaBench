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
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct qla_qpair {struct scsi_qla_host* vha; } ;
struct atio_from_isp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __qlt_send_busy (struct qla_qpair*,struct atio_from_isp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_alloc_qfull_cmd (struct scsi_qla_host*,struct atio_from_isp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qlt_send_busy(struct qla_qpair *qpair, struct atio_from_isp *atio,
    uint16_t status)
{
	int rc = 0;
	struct scsi_qla_host *vha = qpair->vha;

	rc = __qlt_send_busy(qpair, atio, status);
	if (rc == -ENOMEM)
		qlt_alloc_qfull_cmd(vha, atio, status, 1);
}