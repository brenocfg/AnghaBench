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
struct anybuss_host {int /*<<< orphan*/  irq; int /*<<< orphan*/  card_boot; int /*<<< orphan*/  regmap; scalar_t__ power_on; } ;
struct ab_task {int /*<<< orphan*/  task_fn; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  REG_IND_AB ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_deassert (struct anybuss_host*) ; 
 int /*<<< orphan*/  task_fn_power_on_2 ; 

__attribute__((used)) static int task_fn_power_on(struct anybuss_host *cd,
			    struct ab_task *t)
{
	unsigned int dummy;

	if (cd->power_on)
		return 0;
	/*
	 * anybus docs: prevent false 'init done' interrupt by
	 * doing a dummy read of IND_AB register while in reset.
	 */
	regmap_read(cd->regmap, REG_IND_AB, &dummy);
	reinit_completion(&cd->card_boot);
	enable_irq(cd->irq);
	reset_deassert(cd);
	t->task_fn = task_fn_power_on_2;
	return -EINPROGRESS;
}