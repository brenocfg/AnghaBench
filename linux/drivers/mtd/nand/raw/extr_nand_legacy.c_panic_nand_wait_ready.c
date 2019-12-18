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
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ stub1 (struct nand_chip*) ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 

__attribute__((used)) static void panic_nand_wait_ready(struct nand_chip *chip, unsigned long timeo)
{
	int i;

	/* Wait for the device to get ready */
	for (i = 0; i < timeo; i++) {
		if (chip->legacy.dev_ready(chip))
			break;
		touch_softlockup_watchdog();
		mdelay(1);
	}
}