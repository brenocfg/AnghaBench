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
struct ScsiReqBlk {int dummy; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRXFIFO ; 
 int DC395x_read16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int /*<<< orphan*/  TRM_S1040_DMA_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_DMA_FIFOSTAT ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_FIFOCNT ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 

__attribute__((used)) static void cleanup_after_transfer(struct AdapterCtlBlk *acb,
		struct ScsiReqBlk *srb)
{
	/*DC395x_write8 (TRM_S1040_DMA_STATUS, FORCEDMACOMP); */
	if (DC395x_read16(acb, TRM_S1040_DMA_COMMAND) & 0x0001) {	/* read */
		if (!(DC395x_read8(acb, TRM_S1040_SCSI_FIFOCNT) & 0x40))
			clear_fifo(acb, "cleanup/in");
		if (!(DC395x_read8(acb, TRM_S1040_DMA_FIFOSTAT) & 0x80))
			DC395x_write8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
	} else {		/* write */
		if (!(DC395x_read8(acb, TRM_S1040_DMA_FIFOSTAT) & 0x80))
			DC395x_write8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
		if (!(DC395x_read8(acb, TRM_S1040_SCSI_FIFOCNT) & 0x40))
			clear_fifo(acb, "cleanup/out");
	}
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
}