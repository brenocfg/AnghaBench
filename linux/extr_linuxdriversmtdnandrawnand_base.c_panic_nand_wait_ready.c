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
 int /*<<< orphan*/  mdelay (int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 scalar_t__ stub1 (struct mtd_info*) ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 

__attribute__((used)) static void panic_nand_wait_ready(struct mtd_info *mtd, unsigned long timeo)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int i;

	/* Wait for the device to get ready */
	for (i = 0; i < timeo; i++) {
		if (chip->dev_ready(mtd))
			break;
		touch_softlockup_watchdog();
		mdelay(1);
	}
}