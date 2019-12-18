#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct scsi_device {struct Scsi_Host* host; } ;
struct TYPE_7__ {int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {TYPE_3__ SCp; struct scsi_device* device; } ;
struct fib {int flags; scalar_t__ callback_data; TYPE_2__* hw_fib_va; } ;
struct aac_hba_map_info {scalar_t__ devtype; } ;
struct aac_dev {TYPE_4__* pdev; struct aac_hba_map_info** hba_map; struct fib* fibs; } ;
struct Scsi_Host {int can_queue; scalar_t__ hostdata; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ XferState; } ;
struct TYPE_6__ {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ AAC_DEVTYPE_NATIVE_RAW ; 
 int /*<<< orphan*/  AAC_DRIVERNAME ; 
 size_t AAC_MAX_BUSES ; 
 size_t AAC_MAX_TARGETS ; 
 int AAC_NUM_MGT_FIB ; 
 int /*<<< orphan*/  AAC_OWNER_ERROR_HANDLER ; 
 int FAILED ; 
 int FIB_CONTEXT_FLAG ; 
 int FIB_CONTEXT_FLAG_EH_RESET ; 
 int FIB_CONTEXT_FLAG_SCSI_CMD ; 
 int SUCCESS ; 
 int aac_adapter_check_health (struct aac_dev*) ; 
 size_t aac_logical_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int get_num_of_incomplete_fibs (struct aac_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_channel (struct scsi_cmnd*) ; 
 size_t scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_eh_bus_reset(struct scsi_cmnd* cmd)
{
	struct scsi_device * dev = cmd->device;
	struct Scsi_Host * host = dev->host;
	struct aac_dev * aac = (struct aac_dev *)host->hostdata;
	int count;
	u32 cmd_bus;
	int status = 0;


	cmd_bus = aac_logical_to_phys(scmd_channel(cmd));
	/* Mark the assoc. FIB to not complete, eh handler does this */
	for (count = 0; count < (host->can_queue + AAC_NUM_MGT_FIB); ++count) {
		struct fib *fib = &aac->fibs[count];

		if (fib->hw_fib_va->header.XferState &&
		    (fib->flags & FIB_CONTEXT_FLAG) &&
		    (fib->flags & FIB_CONTEXT_FLAG_SCSI_CMD)) {
			struct aac_hba_map_info *info;
			u32 bus, cid;

			cmd = (struct scsi_cmnd *)fib->callback_data;
			bus = aac_logical_to_phys(scmd_channel(cmd));
			if (bus != cmd_bus)
				continue;
			cid = scmd_id(cmd);
			info = &aac->hba_map[bus][cid];
			if (bus >= AAC_MAX_BUSES || cid >= AAC_MAX_TARGETS ||
			    info->devtype != AAC_DEVTYPE_NATIVE_RAW) {
				fib->flags |= FIB_CONTEXT_FLAG_EH_RESET;
				cmd->SCp.phase = AAC_OWNER_ERROR_HANDLER;
			}
		}
	}

	pr_err("%s: Host adapter reset request. SCSI hang ?\n", AAC_DRIVERNAME);

	/*
	 * Check the health of the controller
	 */
	status = aac_adapter_check_health(aac);
	if (status)
		dev_err(&aac->pdev->dev, "Adapter health - %d\n", status);

	count = get_num_of_incomplete_fibs(aac);
	return (count == 0) ? SUCCESS : FAILED;
}