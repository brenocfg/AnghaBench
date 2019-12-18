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
 int /*<<< orphan*/  IR_Idle_Cnt_Low ; 
 int /*<<< orphan*/  IR_Init_Reg ; 
 int SMI_SAMPLE_IDLEMIN ; 
 int SMI_SAMPLE_PERIOD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rbIRen ; 
 int rbIRhighidle ; 
 int /*<<< orphan*/  smi_ir_enableInterrupt (struct smi_rc*) ; 
 int /*<<< orphan*/  smi_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smi_write (int /*<<< orphan*/ ,int) ; 

void smi_ir_start(struct smi_rc *ir)
{
	struct smi_dev *dev = ir->dev;

	smi_write(IR_Idle_Cnt_Low,
		  (((SMI_SAMPLE_PERIOD - 1) & 0xFFFF) << 16) |
		  (SMI_SAMPLE_IDLEMIN & 0xFFFF));
	msleep(20);
	smi_set(IR_Init_Reg, rbIRen | rbIRhighidle);

	smi_ir_enableInterrupt(ir);
}