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
struct denali_controller {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int INTR__INT_ACT ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_controller*) ; 
 int denali_wait_for_irq (struct denali_controller*,int) ; 

__attribute__((used)) static int denali_exec_waitrdy(struct denali_controller *denali)
{
	u32 irq_stat;

	/* R/B# pin transitioned from low to high? */
	irq_stat = denali_wait_for_irq(denali, INTR__INT_ACT);

	/* Just in case nand_operation has multiple NAND_OP_WAITRDY_INSTR. */
	denali_reset_irq(denali);

	return irq_stat & INTR__INT_ACT ? 0 : -EIO;
}