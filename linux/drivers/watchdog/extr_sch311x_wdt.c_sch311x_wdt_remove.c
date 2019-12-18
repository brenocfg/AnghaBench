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
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ runtime_reg; } ;

/* Variables and functions */
 scalar_t__ GP60 ; 
 scalar_t__ WDT_TIME_OUT ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 TYPE_1__ sch311x_wdt_data ; 
 int /*<<< orphan*/  sch311x_wdt_miscdev ; 
 int /*<<< orphan*/  sch311x_wdt_stop () ; 

__attribute__((used)) static int sch311x_wdt_remove(struct platform_device *pdev)
{
	/* Stop the timer before we leave */
	if (!nowayout)
		sch311x_wdt_stop();

	/* Deregister */
	misc_deregister(&sch311x_wdt_miscdev);
	release_region(sch311x_wdt_data.runtime_reg + WDT_TIME_OUT, 4);
	release_region(sch311x_wdt_data.runtime_reg + GP60, 1);
	sch311x_wdt_data.runtime_reg = 0;
	return 0;
}