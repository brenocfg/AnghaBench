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
typedef  size_t u32 ;
struct scsi_cmnd {int result; } ;
struct aac_hba_resp {int status; } ;
struct aac_dev {TYPE_1__** hba_map; } ;
struct TYPE_2__ {int rmw_nexus; int /*<<< orphan*/  devtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_DEVTYPE_ARC_RAW ; 
 int /*<<< orphan*/  AAC_DEVTYPE_NATIVE_RAW ; 
 int ABORT ; 
 int COMMAND_COMPLETE ; 
 int DID_ABORT ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
#define  HBA_RESP_STAT_HBAMODE_DISABLED 134 
#define  HBA_RESP_STAT_INVALID_DEVICE 133 
#define  HBA_RESP_STAT_IO_ABORTED 132 
#define  HBA_RESP_STAT_IO_ERROR 131 
#define  HBA_RESP_STAT_NO_PATH_TO_DEVICE 130 
#define  HBA_RESP_STAT_OVERRUN 129 
#define  HBA_RESP_STAT_UNDERRUN 128 
 int SAM_STAT_BUSY ; 
 size_t aac_logical_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_channel (struct scsi_cmnd*) ; 
 size_t scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static void hba_resp_task_failure(struct aac_dev *dev,
					struct scsi_cmnd *scsicmd,
					struct aac_hba_resp *err)
{
	switch (err->status) {
	case HBA_RESP_STAT_HBAMODE_DISABLED:
	{
		u32 bus, cid;

		bus = aac_logical_to_phys(scmd_channel(scsicmd));
		cid = scmd_id(scsicmd);
		if (dev->hba_map[bus][cid].devtype == AAC_DEVTYPE_NATIVE_RAW) {
			dev->hba_map[bus][cid].devtype = AAC_DEVTYPE_ARC_RAW;
			dev->hba_map[bus][cid].rmw_nexus = 0xffffffff;
		}
		scsicmd->result = DID_NO_CONNECT << 16 | COMMAND_COMPLETE << 8;
		break;
	}
	case HBA_RESP_STAT_IO_ERROR:
	case HBA_RESP_STAT_NO_PATH_TO_DEVICE:
		scsicmd->result = DID_OK << 16 |
			COMMAND_COMPLETE << 8 | SAM_STAT_BUSY;
		break;
	case HBA_RESP_STAT_IO_ABORTED:
		scsicmd->result = DID_ABORT << 16 | ABORT << 8;
		break;
	case HBA_RESP_STAT_INVALID_DEVICE:
		scsicmd->result = DID_NO_CONNECT << 16 | COMMAND_COMPLETE << 8;
		break;
	case HBA_RESP_STAT_UNDERRUN:
		/* UNDERRUN is OK */
		scsicmd->result = DID_OK << 16 | COMMAND_COMPLETE << 8;
		break;
	case HBA_RESP_STAT_OVERRUN:
	default:
		scsicmd->result = DID_ERROR << 16 | COMMAND_COMPLETE << 8;
		break;
	}
}