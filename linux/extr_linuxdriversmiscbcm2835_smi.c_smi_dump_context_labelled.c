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
 int /*<<< orphan*/  SMIDC ; 
 int /*<<< orphan*/  SMIDSR0 ; 
 int /*<<< orphan*/  SMIDSW0 ; 
 int /*<<< orphan*/  SMIFD ; 
 int /*<<< orphan*/  SMIL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_dump_context_labelled(struct bcm2835_smi_instance *inst,
	const char *label)
{
	dev_err(inst->dev, "SMI context dump: %s", label);
	dev_err(inst->dev, "SMICS:  0x%08x", read_smi_reg(inst, SMICS));
	dev_err(inst->dev, "SMIL:   0x%08x", read_smi_reg(inst, SMIL));
	dev_err(inst->dev, "SMIDSR: 0x%08x", read_smi_reg(inst, SMIDSR0));
	dev_err(inst->dev, "SMIDSW: 0x%08x", read_smi_reg(inst, SMIDSW0));
	dev_err(inst->dev, "SMIDC:  0x%08x", read_smi_reg(inst, SMIDC));
	dev_err(inst->dev, "SMIFD:  0x%08x", read_smi_reg(inst, SMIFD));
	dev_err(inst->dev, " ");
}