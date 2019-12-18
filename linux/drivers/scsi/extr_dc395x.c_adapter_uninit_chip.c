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
struct AdapterCtlBlk {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HCC_SCSI_RESET ; 
 int /*<<< orphan*/  TRM_S1040_DMA_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTSTATUS ; 
 int /*<<< orphan*/  reset_scsi_bus (struct AdapterCtlBlk*) ; 

__attribute__((used)) static void adapter_uninit_chip(struct AdapterCtlBlk *acb)
{
	/* disable interrupts */
	DC395x_write8(acb, TRM_S1040_DMA_INTEN, 0);
	DC395x_write8(acb, TRM_S1040_SCSI_INTEN, 0);

	/* reset the scsi bus */
	if (acb->config & HCC_SCSI_RESET)
		reset_scsi_bus(acb);

	/* clear any pending interrupt state */
	DC395x_read8(acb, TRM_S1040_SCSI_INTSTATUS);
}