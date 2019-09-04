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
struct bcm2835_smi_instance {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMICS ; 
 int SMICS_ENABLE ; 
 int /*<<< orphan*/  SMIDCS ; 
 int SMIDCS_ENABLE ; 
 int /*<<< orphan*/  bcm2835_smi_set_regs_from_settings (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_get_default_settings (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  smi_set_address (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_setup_regs(struct bcm2835_smi_instance *inst)
{

	dev_dbg(inst->dev, "Initialising SMI registers...");
	/* Disable the peripheral if already enabled */
	write_smi_reg(inst, 0, SMICS);
	write_smi_reg(inst, 0, SMIDCS);

	smi_get_default_settings(inst);
	bcm2835_smi_set_regs_from_settings(inst);
	smi_set_address(inst, 0);

	write_smi_reg(inst, read_smi_reg(inst, SMICS) | SMICS_ENABLE, SMICS);
	write_smi_reg(inst, read_smi_reg(inst, SMIDCS) | SMIDCS_ENABLE,
		SMIDCS);
}