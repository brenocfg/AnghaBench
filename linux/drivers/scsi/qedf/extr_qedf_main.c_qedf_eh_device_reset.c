#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_TMF_LUN_RESET ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qedf_initiate_tmf (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedf_eh_device_reset(struct scsi_cmnd *sc_cmd)
{
	QEDF_ERR(NULL, "%d:0:%d:%lld: LUN RESET Issued... ",
		 sc_cmd->device->host->host_no, sc_cmd->device->id,
		 sc_cmd->device->lun);
	return qedf_initiate_tmf(sc_cmd, FCP_TMF_LUN_RESET);
}