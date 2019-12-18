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
struct iscsi_cls_host {int /*<<< orphan*/  nr_scans; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

int iscsi_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	struct iscsi_cls_host *ihost = shost->shost_data;
	/*
	 * qla4xxx will have kicked off some session unblocks before calling
	 * scsi_scan_host, so just wait for them to complete.
	 */
	return !atomic_read(&ihost->nr_scans);
}