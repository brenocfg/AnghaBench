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
typedef  int u8 ;
typedef  int u16 ;
struct ctlr_info {TYPE_4__* pdev; } ;
struct TYPE_7__ {int* CDB; int CDBLen; void* type_attr_dir; int /*<<< orphan*/  Timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  LunAddrBytes; } ;
struct TYPE_6__ {int SGList; TYPE_1__ LUN; void* SGTotal; scalar_t__ ReplyQueue; } ;
struct CommandList {TYPE_3__ Request; TYPE_2__ Header; int /*<<< orphan*/  scsi_cmd; int /*<<< orphan*/  cmd_type; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SIMPLE ; 
 int BMIC_CACHE_FLUSH ; 
#define  BMIC_IDENTIFY_CONTROLLER 146 
#define  BMIC_IDENTIFY_PHYSICAL_DEVICE 145 
 void* BMIC_READ ; 
#define  BMIC_SENSE_CONTROLLER_PARAMETERS 144 
#define  BMIC_SENSE_DIAG_OPTIONS 143 
#define  BMIC_SENSE_STORAGE_BOX_PARAMS 142 
#define  BMIC_SENSE_SUBSYSTEM_INFORMATION 141 
#define  BMIC_SET_DIAG_OPTIONS 140 
 void* BMIC_WRITE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CMD_IOCTL_PEND ; 
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int GET_DIR (void*) ; 
#define  HPSA_CACHE_FLUSH 139 
 size_t HPSA_CISS_READ ; 
#define  HPSA_DEVICE_RESET_MSG 138 
#define  HPSA_GET_RAID_MAP 137 
#define  HPSA_INQUIRY 136 
#define  HPSA_PHYS_TARGET_RESET 135 
#define  HPSA_REPORT_LOG 134 
#define  HPSA_REPORT_PHYS 133 
 size_t HPSA_RESET ; 
 int HPSA_RESET_TYPE_LUN ; 
 size_t HPSA_TARGET_RESET_TYPE ; 
#define  RECEIVE_DIAGNOSTIC 132 
 int /*<<< orphan*/  SCSI_CMD_BUSY ; 
#define  TEST_UNIT_READY 131 
 void* TYPE_ATTR_DIR (int,int /*<<< orphan*/ ,int) ; 
 int TYPE_CMD ; 
 int TYPE_MSG ; 
 int VPD_PAGE ; 
#define  XFER_NONE 130 
#define  XFER_READ 129 
#define  XFER_WRITE 128 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ hpsa_map_one (TYPE_4__*,struct CommandList*,void*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_cmd(struct CommandList *c, u8 cmd, struct ctlr_info *h,
	void *buff, size_t size, u16 page_code, unsigned char *scsi3addr,
	int cmd_type)
{
	enum dma_data_direction dir = DMA_NONE;

	c->cmd_type = CMD_IOCTL_PEND;
	c->scsi_cmd = SCSI_CMD_BUSY;
	c->Header.ReplyQueue = 0;
	if (buff != NULL && size > 0) {
		c->Header.SGList = 1;
		c->Header.SGTotal = cpu_to_le16(1);
	} else {
		c->Header.SGList = 0;
		c->Header.SGTotal = cpu_to_le16(0);
	}
	memcpy(c->Header.LUN.LunAddrBytes, scsi3addr, 8);

	if (cmd_type == TYPE_CMD) {
		switch (cmd) {
		case HPSA_INQUIRY:
			/* are we trying to read a vital product page */
			if (page_code & VPD_PAGE) {
				c->Request.CDB[1] = 0x01;
				c->Request.CDB[2] = (page_code & 0xff);
			}
			c->Request.CDBLen = 6;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = HPSA_INQUIRY;
			c->Request.CDB[4] = size & 0xFF;
			break;
		case RECEIVE_DIAGNOSTIC:
			c->Request.CDBLen = 6;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = cmd;
			c->Request.CDB[1] = 1;
			c->Request.CDB[2] = 1;
			c->Request.CDB[3] = (size >> 8) & 0xFF;
			c->Request.CDB[4] = size & 0xFF;
			break;
		case HPSA_REPORT_LOG:
		case HPSA_REPORT_PHYS:
			/* Talking to controller so It's a physical command
			   mode = 00 target = 0.  Nothing to write.
			 */
			c->Request.CDBLen = 12;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = cmd;
			c->Request.CDB[6] = (size >> 24) & 0xFF; /* MSB */
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0xFF;
			c->Request.CDB[9] = size & 0xFF;
			break;
		case BMIC_SENSE_DIAG_OPTIONS:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			/* Spec says this should be BMIC_WRITE */
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_DIAG_OPTIONS;
			break;
		case BMIC_SET_DIAG_OPTIONS:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
					TYPE_ATTR_DIR(cmd_type,
						ATTR_SIMPLE, XFER_WRITE);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_WRITE;
			c->Request.CDB[6] = BMIC_SET_DIAG_OPTIONS;
			break;
		case HPSA_CACHE_FLUSH:
			c->Request.CDBLen = 12;
			c->Request.type_attr_dir =
					TYPE_ATTR_DIR(cmd_type,
						ATTR_SIMPLE, XFER_WRITE);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_WRITE;
			c->Request.CDB[6] = BMIC_CACHE_FLUSH;
			c->Request.CDB[7] = (size >> 8) & 0xFF;
			c->Request.CDB[8] = size & 0xFF;
			break;
		case TEST_UNIT_READY:
			c->Request.CDBLen = 6;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_NONE);
			c->Request.Timeout = 0;
			break;
		case HPSA_GET_RAID_MAP:
			c->Request.CDBLen = 12;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = HPSA_CISS_READ;
			c->Request.CDB[1] = cmd;
			c->Request.CDB[6] = (size >> 24) & 0xFF; /* MSB */
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0xFF;
			c->Request.CDB[9] = size & 0xFF;
			break;
		case BMIC_SENSE_CONTROLLER_PARAMETERS:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_CONTROLLER_PARAMETERS;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0xFF;
			break;
		case BMIC_IDENTIFY_PHYSICAL_DEVICE:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_IDENTIFY_PHYSICAL_DEVICE;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			break;
		case BMIC_SENSE_SUBSYSTEM_INFORMATION:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_SUBSYSTEM_INFORMATION;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			break;
		case BMIC_SENSE_STORAGE_BOX_PARAMS:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[6] = BMIC_SENSE_STORAGE_BOX_PARAMS;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			break;
		case BMIC_IDENTIFY_CONTROLLER:
			c->Request.CDBLen = 10;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_READ);
			c->Request.Timeout = 0;
			c->Request.CDB[0] = BMIC_READ;
			c->Request.CDB[1] = 0;
			c->Request.CDB[2] = 0;
			c->Request.CDB[3] = 0;
			c->Request.CDB[4] = 0;
			c->Request.CDB[5] = 0;
			c->Request.CDB[6] = BMIC_IDENTIFY_CONTROLLER;
			c->Request.CDB[7] = (size >> 16) & 0xFF;
			c->Request.CDB[8] = (size >> 8) & 0XFF;
			c->Request.CDB[9] = 0;
			break;
		default:
			dev_warn(&h->pdev->dev, "unknown command 0x%c\n", cmd);
			BUG();
		}
	} else if (cmd_type == TYPE_MSG) {
		switch (cmd) {

		case  HPSA_PHYS_TARGET_RESET:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_NONE);
			c->Request.Timeout = 0; /* Don't time out */
			memset(&c->Request.CDB[0], 0, sizeof(c->Request.CDB));
			c->Request.CDB[0] = HPSA_RESET;
			c->Request.CDB[1] = HPSA_TARGET_RESET_TYPE;
			/* Physical target reset needs no control bytes 4-7*/
			c->Request.CDB[4] = 0x00;
			c->Request.CDB[5] = 0x00;
			c->Request.CDB[6] = 0x00;
			c->Request.CDB[7] = 0x00;
			break;
		case  HPSA_DEVICE_RESET_MSG:
			c->Request.CDBLen = 16;
			c->Request.type_attr_dir =
				TYPE_ATTR_DIR(cmd_type, ATTR_SIMPLE, XFER_NONE);
			c->Request.Timeout = 0; /* Don't time out */
			memset(&c->Request.CDB[0], 0, sizeof(c->Request.CDB));
			c->Request.CDB[0] =  cmd;
			c->Request.CDB[1] = HPSA_RESET_TYPE_LUN;
			/* If bytes 4-7 are zero, it means reset the */
			/* LunID device */
			c->Request.CDB[4] = 0x00;
			c->Request.CDB[5] = 0x00;
			c->Request.CDB[6] = 0x00;
			c->Request.CDB[7] = 0x00;
			break;
		default:
			dev_warn(&h->pdev->dev, "unknown message type %d\n",
				cmd);
			BUG();
		}
	} else {
		dev_warn(&h->pdev->dev, "unknown command type %d\n", cmd_type);
		BUG();
	}

	switch (GET_DIR(c->Request.type_attr_dir)) {
	case XFER_READ:
		dir = DMA_FROM_DEVICE;
		break;
	case XFER_WRITE:
		dir = DMA_TO_DEVICE;
		break;
	case XFER_NONE:
		dir = DMA_NONE;
		break;
	default:
		dir = DMA_BIDIRECTIONAL;
	}
	if (hpsa_map_one(h->pdev, c, buff, size, dir))
		return -1;
	return 0;
}