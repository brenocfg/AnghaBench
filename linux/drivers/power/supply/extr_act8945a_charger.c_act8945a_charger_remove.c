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
struct act8945a_charger {int init_done; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct act8945a_charger* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int act8945a_charger_remove(struct platform_device *pdev)
{
	struct act8945a_charger *charger = platform_get_drvdata(pdev);

	charger->init_done = false;
	cancel_work_sync(&charger->work);

	return 0;
}