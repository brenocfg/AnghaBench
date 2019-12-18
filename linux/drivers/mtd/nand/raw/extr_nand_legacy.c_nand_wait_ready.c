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
struct TYPE_2__ {scalar_t__ (* dev_ready ) (struct nand_chip*) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ in_interrupt () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 scalar_t__ oops_in_progress ; 
 void panic_nand_wait_ready (struct nand_chip*,unsigned long) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 
 scalar_t__ stub1 (struct nand_chip*) ; 
 scalar_t__ stub2 (struct nand_chip*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

void nand_wait_ready(struct nand_chip *chip)
{
	unsigned long timeo = 400;

	if (in_interrupt() || oops_in_progress)
		return panic_nand_wait_ready(chip, timeo);

	/* Wait until command is processed or timeout occurs */
	timeo = jiffies + msecs_to_jiffies(timeo);
	do {
		if (chip->legacy.dev_ready(chip))
			return;
		cond_resched();
	} while (time_before(jiffies, timeo));

	if (!chip->legacy.dev_ready(chip))
		pr_warn_ratelimited("timeout while waiting for chip to become ready\n");
}