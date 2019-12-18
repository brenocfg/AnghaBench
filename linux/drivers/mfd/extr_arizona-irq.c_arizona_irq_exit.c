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
struct arizona {int /*<<< orphan*/  irq; int /*<<< orphan*/  virq; int /*<<< orphan*/  aod_irq_chip; int /*<<< orphan*/  irq_chip; scalar_t__ ctrlif_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_AOD_IRQ_INDEX ; 
 int /*<<< orphan*/  ARIZONA_IRQ_BOOT_DONE ; 
 int /*<<< orphan*/  ARIZONA_IRQ_CTRLIF_ERR ; 
 int /*<<< orphan*/  ARIZONA_MAIN_IRQ_INDEX ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int /*<<< orphan*/ ,struct arizona*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct arizona*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (unsigned int,int /*<<< orphan*/ ) ; 

int arizona_irq_exit(struct arizona *arizona)
{
	unsigned int virq;

	if (arizona->ctrlif_error)
		arizona_free_irq(arizona, ARIZONA_IRQ_CTRLIF_ERR, arizona);
	arizona_free_irq(arizona, ARIZONA_IRQ_BOOT_DONE, arizona);

	virq = irq_find_mapping(arizona->virq, ARIZONA_MAIN_IRQ_INDEX);
	regmap_del_irq_chip(virq, arizona->irq_chip);
	irq_dispose_mapping(virq);

	virq = irq_find_mapping(arizona->virq, ARIZONA_AOD_IRQ_INDEX);
	regmap_del_irq_chip(virq, arizona->aod_irq_chip);
	irq_dispose_mapping(virq);

	irq_domain_remove(arizona->virq);

	free_irq(arizona->irq, arizona);

	return 0;
}