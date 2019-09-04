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
 int GET_BIT_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMICS ; 
 int SMICS_DONE ; 
 int SMICS_RXD ; 
 int /*<<< orphan*/  SMID ; 
 int /*<<< orphan*/  SMIFD ; 
 int /*<<< orphan*/  SMIFD_FCNT ; 
 scalar_t__ SMI_WIDTH_16BIT ; 
 scalar_t__ SMI_WIDTH_8BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_dump_context_labelled (struct bcm2835_smi_instance*,char*) ; 
 int /*<<< orphan*/  smi_init_programmed_read (struct bcm2835_smi_instance*,int) ; 

__attribute__((used)) static void smi_read_fifo(struct bcm2835_smi_instance *inst,
	uint32_t *dest, int n_bytes)
{
	if (read_smi_reg(inst, SMICS) & SMICS_RXD) {
		smi_dump_context_labelled(inst,
			"WARNING: read FIFO not empty at start of read call.");
		while (read_smi_reg(inst, SMICS))
			;
	}

	/* Dispatch the read: */
	if (inst->settings.data_width == SMI_WIDTH_8BIT)
		smi_init_programmed_read(inst, n_bytes);
	else if (inst->settings.data_width == SMI_WIDTH_16BIT)
		smi_init_programmed_read(inst, n_bytes / 2);
	else {
		dev_err(inst->dev, "Unsupported data width for read.");
		return;
	}

	/* Poll FIFO to keep it empty */
	while (!(read_smi_reg(inst, SMICS) & SMICS_DONE))
		if (read_smi_reg(inst, SMICS) & SMICS_RXD)
			*dest++ = read_smi_reg(inst, SMID);

	/* Ensure that the FIFO is emptied */
	if (read_smi_reg(inst, SMICS) & SMICS_RXD) {
		int fifo_count;

		fifo_count = GET_BIT_FIELD(read_smi_reg(inst, SMIFD),
			SMIFD_FCNT);
		while (fifo_count--)
			*dest++ = read_smi_reg(inst, SMID);
	}

	if (!(read_smi_reg(inst, SMICS) & SMICS_DONE))
		smi_dump_context_labelled(inst,
			"WARNING: transaction finished but done bit not set.");

	if (read_smi_reg(inst, SMICS) & SMICS_RXD)
		smi_dump_context_labelled(inst,
			"WARNING: read FIFO not empty at end of read call.");

}