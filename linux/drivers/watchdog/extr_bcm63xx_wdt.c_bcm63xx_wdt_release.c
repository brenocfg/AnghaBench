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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 TYPE_1__ bcm63xx_wdt_device ; 
 int /*<<< orphan*/  bcm63xx_wdt_pause () ; 
 int /*<<< orphan*/  bcm63xx_wdt_start () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static int bcm63xx_wdt_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42)
		bcm63xx_wdt_pause();
	else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		bcm63xx_wdt_start();
	}
	clear_bit(0, &bcm63xx_wdt_device.inuse);
	expect_close = 0;
	return 0;
}