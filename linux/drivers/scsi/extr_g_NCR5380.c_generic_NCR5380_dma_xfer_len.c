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
struct TYPE_2__ {int this_residual; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; TYPE_1__ SCp; } ;
struct NCR5380_hostdata {int flags; scalar_t__ board; } ;

/* Variables and functions */
 scalar_t__ BOARD_DTC3181E ; 
 int DMA_MAX_SIZE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int FLAG_NO_PSEUDO_DMA ; 
 int min (int,int) ; 

__attribute__((used)) static int generic_NCR5380_dma_xfer_len(struct NCR5380_hostdata *hostdata,
                                        struct scsi_cmnd *cmd)
{
	int transfersize = cmd->SCp.this_residual;

	if (hostdata->flags & FLAG_NO_PSEUDO_DMA)
		return 0;

	/* 53C400 datasheet: non-modulo-128-byte transfers should use PIO */
	if (transfersize % 128)
		return 0;

	/* Limit PDMA send to 512 B to avoid random corruption on DTC3181E */
	if (hostdata->board == BOARD_DTC3181E &&
	    cmd->sc_data_direction == DMA_TO_DEVICE)
		transfersize = min(cmd->SCp.this_residual, 512);

	return min(transfersize, DMA_MAX_SIZE);
}