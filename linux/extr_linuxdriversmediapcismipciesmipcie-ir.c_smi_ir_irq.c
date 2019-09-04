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
typedef  int u32 ;
struct smi_rc {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int IR_X_INT ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smi_ir_clearInterrupt (struct smi_rc*) ; 
 int /*<<< orphan*/  smi_ir_disableInterrupt (struct smi_rc*) ; 

int smi_ir_irq(struct smi_rc *ir, u32 int_status)
{
	int handled = 0;

	if (int_status & IR_X_INT) {
		smi_ir_disableInterrupt(ir);
		smi_ir_clearInterrupt(ir);
		schedule_work(&ir->work);
		handled = 1;
	}
	return handled;
}