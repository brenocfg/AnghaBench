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
struct TYPE_16__ {int /*<<< orphan*/  dma_direction; TYPE_5__* pthru; } ;
typedef  TYPE_4__ scb_t ;
struct TYPE_17__ {int timeout; int ars; int reqsenselen; int channel; int target; int /*<<< orphan*/  dataxferlen; int /*<<< orphan*/  dataxferaddr; int /*<<< orphan*/  numsgelements; int /*<<< orphan*/  cdb; int /*<<< orphan*/  logdrv; int /*<<< orphan*/  cdblen; scalar_t__ islogical; } ;
typedef  TYPE_5__ mega_passthru ;
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

__attribute__((used)) static mega_passthru *
mega_prepare_passthru(adapter_t *adapter, scb_t *scb, struct scsi_cmnd *cmd,
		      int channel, int target)
{
	mega_passthru *pthru;

	pthru = scb->pthru;
	memset(pthru, 0, sizeof (mega_passthru));

	/* 0=6sec/1=60sec/2=10min/3=3hrs */
	pthru->timeout = 2;

	pthru->ars = 1;
	pthru->reqsenselen = 14;
	pthru->islogical = 0;

	pthru->channel = (adapter->flag & BOARD_40LD) ? 0 : channel;

	pthru->target = (adapter->flag & BOARD_40LD) ?
		(channel << 4) | target : target;

	pthru->cdblen = cmd->cmd_len;
	pthru->logdrv = cmd->device->lun;

	memcpy(pthru->cdb, cmd->cmnd, cmd->cmd_len);

	/* Not sure about the direction */
	scb->dma_direction = PCI_DMA_BIDIRECTIONAL;

	/* Special Code for Handling READ_CAPA/ INQ using bounce buffers */
	switch (cmd->cmnd[0]) {
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
		pthru->numsgelements = mega_build_sglist(adapter, scb,
				&pthru->dataxferaddr, &pthru->dataxferlen);
		break;
	}
	return pthru;
}