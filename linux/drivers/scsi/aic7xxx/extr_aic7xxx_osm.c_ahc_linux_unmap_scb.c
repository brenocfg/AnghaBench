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
struct scsi_cmnd {int dummy; } ;
struct scb {struct scsi_cmnd* io_ctx; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  ahc_sync_sglist (struct ahc_softc*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 

__attribute__((used)) static void
ahc_linux_unmap_scb(struct ahc_softc *ahc, struct scb *scb)
{
	struct scsi_cmnd *cmd;

	cmd = scb->io_ctx;
	ahc_sync_sglist(ahc, scb, BUS_DMASYNC_POSTWRITE);

	scsi_dma_unmap(cmd);
}