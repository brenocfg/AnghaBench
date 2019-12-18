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
typedef  int u8 ;
typedef  int u16 ;
struct AdapterCtlBlk {int sel_timeout; int config; TYPE_1__* scsi_host; } ;
struct TYPE_2__ {int this_id; } ;

/* Variables and functions */
 int BLOCKRST ; 
 int DC395x_read16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int DMA_ENHANCE ; 
 int DMA_FIFO_CTRL ; 
 int DMA_FIFO_HALF_HALF ; 
 int EN_DMAXFERERROR ; 
 int EN_SCSIINTR ; 
 int HCC_PARITY ; 
 int INITIATOR ; 
 int PARITYCHECK ; 
 int PHASELATCH ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CONFIG ; 
 int /*<<< orphan*/  TRM_S1040_DMA_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_GEN_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONFIG0 ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONFIG1 ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_HOSTID ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTSTATUS ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_OFFSET ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_TIMEOUT ; 

__attribute__((used)) static void set_basic_config(struct AdapterCtlBlk *acb)
{
	u8 bval;
	u16 wval;
	DC395x_write8(acb, TRM_S1040_SCSI_TIMEOUT, acb->sel_timeout);
	if (acb->config & HCC_PARITY)
		bval = PHASELATCH | INITIATOR | BLOCKRST | PARITYCHECK;
	else
		bval = PHASELATCH | INITIATOR | BLOCKRST;

	DC395x_write8(acb, TRM_S1040_SCSI_CONFIG0, bval);

	/* program configuration 1: Act_Neg (+ Act_Neg_Enh? + Fast_Filter? + DataDis?) */
	DC395x_write8(acb, TRM_S1040_SCSI_CONFIG1, 0x03);	/* was 0x13: default */
	/* program Host ID                  */
	DC395x_write8(acb, TRM_S1040_SCSI_HOSTID, acb->scsi_host->this_id);
	/* set ansynchronous transfer       */
	DC395x_write8(acb, TRM_S1040_SCSI_OFFSET, 0x00);
	/* Turn LED control off */
	wval = DC395x_read16(acb, TRM_S1040_GEN_CONTROL) & 0x7F;
	DC395x_write16(acb, TRM_S1040_GEN_CONTROL, wval);
	/* DMA config          */
	wval = DC395x_read16(acb, TRM_S1040_DMA_CONFIG) & ~DMA_FIFO_CTRL;
	wval |=
	    DMA_FIFO_HALF_HALF | DMA_ENHANCE /*| DMA_MEM_MULTI_READ */ ;
	DC395x_write16(acb, TRM_S1040_DMA_CONFIG, wval);
	/* Clear pending interrupt status */
	DC395x_read8(acb, TRM_S1040_SCSI_INTSTATUS);
	/* Enable SCSI interrupt    */
	DC395x_write8(acb, TRM_S1040_SCSI_INTEN, 0x7F);
	DC395x_write8(acb, TRM_S1040_DMA_INTEN, EN_SCSIINTR | EN_DMAXFERERROR
		      /*| EN_DMAXFERABORT | EN_DMAXFERCOMP | EN_FORCEDMACOMP */
		      );
}