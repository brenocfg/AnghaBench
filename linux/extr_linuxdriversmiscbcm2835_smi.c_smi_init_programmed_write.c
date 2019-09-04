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
struct bcm2835_smi_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMICS ; 
 int SMICS_ENABLE ; 
 int SMICS_START ; 
 int SMICS_WRITE ; 
 int /*<<< orphan*/  SMIL ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_init_programmed_write(struct bcm2835_smi_instance *inst,
	int num_transfers)
{
	int smics_temp;

	/* Disable the peripheral: */
	smics_temp = read_smi_reg(inst, SMICS) & ~SMICS_ENABLE;
	write_smi_reg(inst, smics_temp, SMICS);
	while (read_smi_reg(inst, SMICS) & SMICS_ENABLE)
		;

	/* Program the transfer count: */
	write_smi_reg(inst, num_transfers, SMIL);

	/* setup, re-enable and start: */
	smics_temp |= SMICS_WRITE | SMICS_ENABLE;
	write_smi_reg(inst, smics_temp, SMICS);
	smics_temp |= SMICS_START;
	write_smi_reg(inst, smics_temp, SMICS);
}