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
struct scsi_qla_host {int dummy; } ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla2x00_mark_device_lost (struct scsi_qla_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qlafx00_get_fcport (struct scsi_qla_host*,int) ; 

__attribute__((used)) static void
qlafx00_tgt_detach(struct scsi_qla_host *vha, int tgt_id)
{
	fc_port_t	*fcport;

	ql_log(ql_log_info, vha, 0x5073,
	    "Detach TGT-ID: 0x%x\n", tgt_id);

	fcport = qlafx00_get_fcport(vha, tgt_id);
	if (!fcport)
		return;

	qla2x00_mark_device_lost(vha, fcport, 0, 0);

	return;
}