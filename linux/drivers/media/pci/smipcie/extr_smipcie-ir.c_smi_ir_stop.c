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
struct smi_rc {struct smi_dev* dev; } ;
struct smi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IR_Init_Reg ; 
 int /*<<< orphan*/  rbIRen ; 
 int /*<<< orphan*/  smi_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_ir_disableInterrupt (struct smi_rc*) ; 

__attribute__((used)) static void smi_ir_stop(struct smi_rc *ir)
{
	struct smi_dev *dev = ir->dev;

	smi_ir_disableInterrupt(ir);
	smi_clear(IR_Init_Reg, rbIRen);
}