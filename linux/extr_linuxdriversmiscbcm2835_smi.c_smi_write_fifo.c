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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ data_width; } ;
struct bcm2835_smi_instance {int /*<<< orphan*/  dev; TYPE_1__ settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMICS ; 
 int SMICS_CLEAR ; 
 int SMICS_DONE ; 
 int SMICS_TXD ; 
 int SMICS_TXE ; 
 int /*<<< orphan*/  SMID ; 
 scalar_t__ SMI_WIDTH_16BIT ; 
 scalar_t__ SMI_WIDTH_8BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_dump_context_labelled (struct bcm2835_smi_instance*,char*) ; 
 int /*<<< orphan*/  smi_init_programmed_write (struct bcm2835_smi_instance*,int) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_write_fifo(struct bcm2835_smi_instance *inst,
	uint32_t *src, int n_bytes)
{
	int i, timeout = 0;

	/* Empty FIFOs if not already so */
	if (!(read_smi_reg(inst, SMICS) & SMICS_TXE)) {
		smi_dump_context_labelled(inst,
		    "WARNING: write fifo not empty at start of write call.");
		write_smi_reg(inst, read_smi_reg(inst, SMICS) | SMICS_CLEAR,
			SMICS);
	}

	/* Initiate the transfer */
	if (inst->settings.data_width == SMI_WIDTH_8BIT)
		smi_init_programmed_write(inst, n_bytes);
	else if (inst->settings.data_width == SMI_WIDTH_16BIT)
		smi_init_programmed_write(inst, n_bytes / 2);
	else {
		dev_err(inst->dev, "Unsupported data width for write.");
		return;
	}
	/* Fill the FIFO: */
	for (i = 0; i < (n_bytes - 1) / 4 + 1; ++i) {
		while (!(read_smi_reg(inst, SMICS) & SMICS_TXD))
			;
		write_smi_reg(inst, *src++, SMID);
	}
	/* Busy wait... */
	while (!(read_smi_reg(inst, SMICS) & SMICS_DONE) && ++timeout <
		1000000)
		;
	if (timeout >= 1000000)
		smi_dump_context_labelled(inst,
			"Timed out on write operation!");
	if (!(read_smi_reg(inst, SMICS) & SMICS_TXE))
		smi_dump_context_labelled(inst,
			"WARNING: FIFO not empty at end of write operation.");
}