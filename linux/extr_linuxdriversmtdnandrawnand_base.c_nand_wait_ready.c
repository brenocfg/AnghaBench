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
struct nand_chip {scalar_t__ (* dev_ready ) (struct mtd_info*) ;} ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ in_interrupt () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 scalar_t__ oops_in_progress ; 
 void panic_nand_wait_ready (struct mtd_info*,unsigned long) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 
 scalar_t__ stub1 (struct mtd_info*) ; 
 scalar_t__ stub2 (struct mtd_info*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

void nand_wait_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	unsigned long timeo = 400;

	if (in_interrupt() || oops_in_progress)
		return panic_nand_wait_ready(mtd, timeo);

	/* Wait until command is processed or timeout occurs */
	timeo = jiffies + msecs_to_jiffies(timeo);
	do {
		if (chip->dev_ready(mtd))
			return;
		cond_resched();
	} while (time_before(jiffies, timeo));

	if (!chip->dev_ready(mtd))
		pr_warn_ratelimited("timeout while waiting for chip to become ready\n");
}