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
struct TYPE_3__ {scalar_t__ command; } ;
struct ata_queued_cmd {TYPE_2__* scsicmd; TYPE_1__ tf; struct ata_port* ap; } ;
struct ata_port {int dummy; } ;
struct TYPE_4__ {scalar_t__ sc_data_direction; } ;

/* Variables and functions */
 scalar_t__ ATA_CMD_PACKET ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ata_bmdma_start (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_sff_pause (struct ata_port*) ; 

__attribute__((used)) static void vt6420_bmdma_start(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	if ((qc->tf.command == ATA_CMD_PACKET) &&
	    (qc->scsicmd->sc_data_direction == DMA_TO_DEVICE)) {
		/* Prevents corruption on some ATAPI burners */
		ata_sff_pause(ap);
	}
	ata_bmdma_start(qc);
}