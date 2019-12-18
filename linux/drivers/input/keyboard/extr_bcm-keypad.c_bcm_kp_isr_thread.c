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
struct bcm_kp {int kpcr; int /*<<< orphan*/  input_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KPCR_MODE_MASK ; 
 int KPCR_MODE_SHIFT ; 
 int /*<<< orphan*/  bcm_kp_report_keys (struct bcm_kp*,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bcm_kp_isr_thread(int irq, void *dev_id)
{
	struct bcm_kp *kp = dev_id;
	int pull_mode = (kp->kpcr >> KPCR_MODE_SHIFT) & KPCR_MODE_MASK;
	int reg_num;

	for (reg_num = 0; reg_num <= 1; reg_num++)
		bcm_kp_report_keys(kp, reg_num, pull_mode);

	input_sync(kp->input_dev);

	return IRQ_HANDLED;
}