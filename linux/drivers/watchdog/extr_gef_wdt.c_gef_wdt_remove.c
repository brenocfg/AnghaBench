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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gef_wdt_handler_disable () ; 
 int /*<<< orphan*/  gef_wdt_miscdev ; 
 int /*<<< orphan*/  gef_wdt_regs ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gef_wdt_remove(struct platform_device *dev)
{
	misc_deregister(&gef_wdt_miscdev);

	gef_wdt_handler_disable();

	iounmap(gef_wdt_regs);

	return 0;
}