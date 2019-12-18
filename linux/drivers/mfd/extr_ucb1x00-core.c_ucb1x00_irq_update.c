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
struct ucb1x00 {unsigned int irq_ris_enbl; int irq_mask; unsigned int irq_fal_enbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IE_FAL ; 
 int /*<<< orphan*/  UCB_IE_RIS ; 
 int /*<<< orphan*/  ucb1x00_disable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_enable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ucb1x00_irq_update(struct ucb1x00 *ucb, unsigned mask)
{
	ucb1x00_enable(ucb);
	if (ucb->irq_ris_enbl & mask)
		ucb1x00_reg_write(ucb, UCB_IE_RIS, ucb->irq_ris_enbl &
				  ucb->irq_mask);
	if (ucb->irq_fal_enbl & mask)
		ucb1x00_reg_write(ucb, UCB_IE_FAL, ucb->irq_fal_enbl &
				  ucb->irq_mask);
	ucb1x00_disable(ucb);
}