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
struct max8925_power_info {struct max8925_chip* chip; } ;
struct max8925_chip {int irq_base; } ;

/* Variables and functions */
 int MAX8925_IRQ_VCHG_DC_OVP ; 
 int MAX8925_IRQ_VCHG_TMR_FAULT ; 
 int /*<<< orphan*/  free_irq (int,struct max8925_power_info*) ; 

__attribute__((used)) static int max8925_deinit_charger(struct max8925_power_info *info)
{
	struct max8925_chip *chip = info->chip;
	int irq;

	irq = chip->irq_base + MAX8925_IRQ_VCHG_DC_OVP;
	for (; irq <= chip->irq_base + MAX8925_IRQ_VCHG_TMR_FAULT; irq++)
		free_irq(irq, info);

	return 0;
}