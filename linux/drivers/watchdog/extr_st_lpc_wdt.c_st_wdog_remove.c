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
struct st_wdog {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  st_wdog_dev ; 
 int /*<<< orphan*/  st_wdog_setup (struct st_wdog*,int) ; 
 struct st_wdog* watchdog_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_wdog_remove(struct platform_device *pdev)
{
	struct st_wdog *st_wdog = watchdog_get_drvdata(&st_wdog_dev);

	st_wdog_setup(st_wdog, false);

	return 0;
}