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
typedef  int uint32_t ;
struct bcm2835_smi_instance {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMIDCS ; 
 int SMIDCS_DONE ; 
 int SMIDCS_ENABLE ; 
 int SMIDCS_START ; 
 int /*<<< orphan*/  SMIDD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mb () ; 
 int read_smi_reg (struct bcm2835_smi_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_smi_reg (struct bcm2835_smi_instance*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t smi_read_single_word(struct bcm2835_smi_instance *inst)
{
	int timeout = 0;

	write_smi_reg(inst, SMIDCS_ENABLE, SMIDCS);
	write_smi_reg(inst, SMIDCS_ENABLE | SMIDCS_START, SMIDCS);
	/* Make sure things happen in the right order...*/
	mb();
	while (!(read_smi_reg(inst, SMIDCS) & SMIDCS_DONE) &&
		++timeout < 10000)
		;
	if (timeout < 10000)
		return read_smi_reg(inst, SMIDD);

	dev_err(inst->dev,
		"SMI direct read timed out (is the clock set up correctly?)");
	return 0;
}