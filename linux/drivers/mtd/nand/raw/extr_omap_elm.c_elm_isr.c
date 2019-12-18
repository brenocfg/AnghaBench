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
struct elm_info {int /*<<< orphan*/  elm_completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELM_IRQSTATUS ; 
 int INTR_STATUS_PAGE_VALID ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int elm_read_reg (struct elm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elm_write_reg (struct elm_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t elm_isr(int this_irq, void *dev_id)
{
	u32 reg_val;
	struct elm_info *info = dev_id;

	reg_val = elm_read_reg(info, ELM_IRQSTATUS);

	/* All error vectors processed */
	if (reg_val & INTR_STATUS_PAGE_VALID) {
		elm_write_reg(info, ELM_IRQSTATUS,
				reg_val & INTR_STATUS_PAGE_VALID);
		complete(&info->elm_completion);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}