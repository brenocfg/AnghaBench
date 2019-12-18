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
struct scsi_qla_host {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_host_for_each_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4xxx_mark_device_missing ; 

void qla4xxx_mark_all_devices_missing(struct scsi_qla_host *ha)
{
	iscsi_host_for_each_session(ha->host, qla4xxx_mark_device_missing);
}