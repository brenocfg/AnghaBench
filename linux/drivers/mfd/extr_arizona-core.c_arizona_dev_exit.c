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
struct arizona {int /*<<< orphan*/  core_supplies; int /*<<< orphan*/  num_core_supplies; int /*<<< orphan*/  dev; int /*<<< orphan*/  dcvdd; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_IRQ_CLKGEN_ERR ; 
 int /*<<< orphan*/  ARIZONA_IRQ_OVERCLOCKED ; 
 int /*<<< orphan*/  ARIZONA_IRQ_UNDERCLOCKED ; 
 int /*<<< orphan*/  arizona_enable_reset (struct arizona*) ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int /*<<< orphan*/ ,struct arizona*) ; 
 int /*<<< orphan*/  arizona_irq_exit (struct arizona*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

int arizona_dev_exit(struct arizona *arizona)
{
	disable_irq(arizona->irq);
	pm_runtime_disable(arizona->dev);

	regulator_disable(arizona->dcvdd);
	regulator_put(arizona->dcvdd);

	mfd_remove_devices(arizona->dev);
	arizona_free_irq(arizona, ARIZONA_IRQ_UNDERCLOCKED, arizona);
	arizona_free_irq(arizona, ARIZONA_IRQ_OVERCLOCKED, arizona);
	arizona_free_irq(arizona, ARIZONA_IRQ_CLKGEN_ERR, arizona);
	arizona_irq_exit(arizona);
	arizona_enable_reset(arizona);

	regulator_bulk_disable(arizona->num_core_supplies,
			       arizona->core_supplies);
	return 0;
}