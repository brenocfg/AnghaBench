#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int* cmnd; TYPE_3__* device; int /*<<< orphan*/  cmd_len; } ;
struct TYPE_16__ {int /*<<< orphan*/  dma_direction; TYPE_5__* epthru; } ;
typedef  TYPE_4__ scb_t ;
struct TYPE_17__ {int timeout; int ars; int reqsenselen; int channel; int target; int /*<<< orphan*/  dataxferlen; int /*<<< orphan*/  dataxferaddr; int /*<<< orphan*/  numsgelements; int /*<<< orphan*/  cdb; int /*<<< orphan*/  logdrv; int /*<<< orphan*/  cdblen; scalar_t__ islogical; } ;
typedef  TYPE_5__ mega_ext_passthru ;
struct TYPE_18__ {int flag; TYPE_2__* host; TYPE_1__* dev; } ;
typedef  TYPE_6__ adapter_t ;
struct TYPE_15__ {long channel; int /*<<< orphan*/  lun; } ;
struct TYPE_14__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BOARD_40LD ; 
#define  INQUIRY 129 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
#define  READ_CAPACITY 128 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  mega_build_sglist (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static mega_ext_passthru *
mega_prepare_extpassthru(adapter_t *adapter, scb_t *scb,
			 struct scsi_cmnd *cmd,
			 int channel, int target)
{
	mega_ext_passthru	*epthru;

	epthru = scb->epthru;
	memset(epthru, 0, sizeof(mega_ext_passthru));

	/* 0=6sec/1=60sec/2=10min/3=3hrs */
	epthru->timeout = 2;

	epthru->ars = 1;
	epthru->reqsenselen = 14;
	epthru->islogical = 0;

	epthru->channel = (adapter->flag & BOARD_40LD) ? 0 : channel;
	epthru->target = (adapter->flag & BOARD_40LD) ?
		(channel << 4) | target : target;

	epthru->cdblen = cmd->cmd_len;
	epthru->logdrv = cmd->device->lun;

	memcpy(epthru->cdb, cmd->cmnd, cmd->cmd_len);

	/* Not sure about the direction */
	scb->dma_direction = PCI_DMA_BIDIRECTIONAL;

	switch(cmd->cmnd[0]) {
	case INQUIRY:
	case READ_CAPACITY:
		if(!(adapter->flag & (1L << cmd->device->channel))) {

			dev_notice(&adapter->dev->dev,
				"scsi%d: scanning scsi channel %d [P%d] "
				"for physical devices\n",
					adapter->host->host_no,
					cmd->device->channel, channel);

			adapter->flag |= (1L << cmd->device->channel);
		}
		/* Fall through */
	default:
		epthru->numsgelements = mega_build_sglist(adapter, scb,
				&epthru->dataxferaddr, &epthru->dataxferlen);
		break;
	}

	return epthru;
}