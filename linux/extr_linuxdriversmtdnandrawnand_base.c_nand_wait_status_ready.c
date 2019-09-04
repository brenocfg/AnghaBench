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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int NAND_STATUS_READY ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_read_data_op (struct nand_chip*,int*,int,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 

__attribute__((used)) static void nand_wait_status_ready(struct mtd_info *mtd, unsigned long timeo)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	int ret;

	timeo = jiffies + msecs_to_jiffies(timeo);
	do {
		u8 status;

		ret = nand_read_data_op(chip, &status, sizeof(status), true);
		if (ret)
			return;

		if (status & NAND_STATUS_READY)
			break;
		touch_softlockup_watchdog();
	} while (time_before(jiffies, timeo));
}