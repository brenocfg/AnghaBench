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
struct scsi_qla_host {int /*<<< orphan*/  fw_dump_skip_size; int /*<<< orphan*/  host_no; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry_capture_mask; int /*<<< orphan*/  driver_flags; } ;
struct qla8xxx_minidump_entry_hdr {scalar_t__ entry_capture_size; TYPE_1__ d_ctrl; int /*<<< orphan*/  entry_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  QLA8XXX_DBG_SKIPPED_FLAG ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4_8xxx_mark_entry_skipped(struct scsi_qla_host *ha,
				struct qla8xxx_minidump_entry_hdr *entry_hdr,
				int index)
{
	entry_hdr->d_ctrl.driver_flags |= QLA8XXX_DBG_SKIPPED_FLAG;
	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "scsi(%ld): Skipping entry[%d]: ETYPE[0x%x]-ELEVEL[0x%x]\n",
			  ha->host_no, index, entry_hdr->entry_type,
			  entry_hdr->d_ctrl.entry_capture_mask));
	/* If driver encounters a new entry type that it cannot process,
	 * it should just skip the entry and adjust the total buffer size by
	 * from subtracting the skipped bytes from it
	 */
	ha->fw_dump_skip_size += entry_hdr->entry_capture_size;
}