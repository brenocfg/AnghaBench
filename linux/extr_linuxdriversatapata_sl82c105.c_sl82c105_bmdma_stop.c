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
struct ata_queued_cmd {int /*<<< orphan*/  dev; struct ata_port* ap; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_bmdma_stop (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  sl82c105_reset_engine (struct ata_port*) ; 
 int /*<<< orphan*/  sl82c105_set_piomode (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sl82c105_bmdma_stop(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	ata_bmdma_stop(qc);
	sl82c105_reset_engine(ap);
	udelay(100);

	/* This will redo the initial setup of the DMA device to matching
	   PIO timings */
	sl82c105_set_piomode(ap, qc->dev);
}