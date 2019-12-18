#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; struct TYPE_10__* q_next; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data_busaddr; int /*<<< orphan*/  scsi_cmd; } ;
typedef  TYPE_2__ ips_scb_t ;
struct TYPE_11__ {int max_cmds; TYPE_2__* scb_freelist; TYPE_1__* pcidev; } ;
typedef  TYPE_3__ ips_ha_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IPS_COMMAND_ID (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IPS_DMA_DIR (TYPE_2__*) ; 
 int IPS_SCB_MAP_SG ; 
 int IPS_SCB_MAP_SINGLE ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dma_unmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ips_freescb(ips_ha_t * ha, ips_scb_t * scb)
{

	METHOD_TRACE("ips_freescb", 1);
	if (scb->flags & IPS_SCB_MAP_SG)
                scsi_dma_unmap(scb->scsi_cmd);
	else if (scb->flags & IPS_SCB_MAP_SINGLE)
		dma_unmap_single(&ha->pcidev->dev, scb->data_busaddr,
				 scb->data_len, IPS_DMA_DIR(scb));

	/* check to make sure this is not our "special" scb */
	if (IPS_COMMAND_ID(ha, scb) < (ha->max_cmds - 1)) {
		scb->q_next = ha->scb_freelist;
		ha->scb_freelist = scb;
	}
}