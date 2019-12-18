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
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 TYPE_1__ rc32434_wdt_device ; 
 int /*<<< orphan*/  rc32434_wdt_ping () ; 
 int /*<<< orphan*/  rc32434_wdt_stop () ; 

__attribute__((used)) static int rc32434_wdt_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42) {
		rc32434_wdt_stop();
		module_put(THIS_MODULE);
	} else {
		pr_crit("device closed unexpectedly. WDT will not stop!\n");
		rc32434_wdt_ping();
	}
	clear_bit(0, &rc32434_wdt_device.inuse);
	return 0;
}