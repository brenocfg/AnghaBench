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
typedef  int u8 ;
struct nand_chip {scalar_t__ (* dev_ready ) (struct mtd_info*) ;} ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ in_interrupt () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int nand_read_data_op (struct nand_chip*,int*,int,int) ; 
 int nand_status_op (struct nand_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  panic_nand_wait (struct mtd_info*,struct nand_chip*,unsigned long) ; 
 scalar_t__ stub1 (struct mtd_info*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int nand_wait(struct mtd_info *mtd, struct nand_chip *chip)
{

	unsigned long timeo = 400;
	u8 status;
	int ret;

	/*
	 * Apply this short delay always to ensure that we do wait tWB in any
	 * case on any machine.
	 */
	ndelay(100);

	ret = nand_status_op(chip, NULL);
	if (ret)
		return ret;

	if (in_interrupt() || oops_in_progress)
		panic_nand_wait(mtd, chip, timeo);
	else {
		timeo = jiffies + msecs_to_jiffies(timeo);
		do {
			if (chip->dev_ready) {
				if (chip->dev_ready(mtd))
					break;
			} else {
				ret = nand_read_data_op(chip, &status,
							sizeof(status), true);
				if (ret)
					return ret;

				if (status & NAND_STATUS_READY)
					break;
			}
			cond_resched();
		} while (time_before(jiffies, timeo));
	}

	ret = nand_read_data_op(chip, &status, sizeof(status), true);
	if (ret)
		return ret;

	/* This can happen if in case of timeout or buggy dev_ready */
	WARN_ON(!(status & NAND_STATUS_READY));
	return status;
}