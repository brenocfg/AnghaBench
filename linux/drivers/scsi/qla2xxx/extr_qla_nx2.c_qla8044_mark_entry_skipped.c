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
struct scsi_qla_host {int /*<<< orphan*/  host_no; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry_capture_mask; int /*<<< orphan*/  driver_flags; } ;
struct qla8044_minidump_entry_hdr {TYPE_1__ d_ctrl; int /*<<< orphan*/  entry_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_DBG_SKIPPED_FLAG ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_info ; 

__attribute__((used)) static void
qla8044_mark_entry_skipped(struct scsi_qla_host *vha,
	struct qla8044_minidump_entry_hdr *entry_hdr, int index)
{
	entry_hdr->d_ctrl.driver_flags |= QLA82XX_DBG_SKIPPED_FLAG;

	ql_log(ql_log_info, vha, 0xb0f7,
	    "scsi(%ld): Skipping entry[%d]: ETYPE[0x%x]-ELEVEL[0x%x]\n",
	    vha->host_no, index, entry_hdr->entry_type,
	    entry_hdr->d_ctrl.entry_capture_mask);
}