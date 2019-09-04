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
struct irq_data {int irq; } ;
struct TYPE_2__ {int int_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MFP_TIMD ; 
 int IRQ_MFP_TIMER1 ; 
 int /*<<< orphan*/  atari_enable_irq (int /*<<< orphan*/ ) ; 
 TYPE_1__ stmfp_base ; 

__attribute__((used)) static void atari_mfptimer_enable(struct irq_data *data)
{
	int mfp_num = data->irq - IRQ_MFP_TIMER1;
	stmfp_base.int_mask |= 1 << mfp_num;
	atari_enable_irq(IRQ_MFP_TIMD);
}