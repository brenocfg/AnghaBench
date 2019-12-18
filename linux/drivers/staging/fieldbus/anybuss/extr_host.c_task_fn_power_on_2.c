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
struct anybuss_host {int power_on; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  card_boot; } ;
struct ab_task {scalar_t__ start_jiffies; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ETIMEDOUT ; 
 scalar_t__ TIMEOUT ; 
 scalar_t__ completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  reset_assert (struct anybuss_host*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int task_fn_power_on_2(struct anybuss_host *cd,
			      struct ab_task *t)
{
	if (completion_done(&cd->card_boot)) {
		cd->power_on = true;
		return 0;
	}
	if (time_after(jiffies, t->start_jiffies + TIMEOUT)) {
		disable_irq(cd->irq);
		reset_assert(cd);
		dev_err(cd->dev, "power on timed out");
		return -ETIMEDOUT;
	}
	return -EINPROGRESS;
}