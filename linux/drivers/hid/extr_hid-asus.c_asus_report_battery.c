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
typedef  int /*<<< orphan*/  u8 ;
struct asus_drvdata {int battery_in_query; int /*<<< orphan*/  battery; } ;

/* Variables and functions */
 int BATTERY_REPORT_SIZE ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_report_battery(struct asus_drvdata *drvdata, u8 *data, int size)
{
	/* notify only the autonomous event by device */
	if ((drvdata->battery_in_query == false) &&
			 (size == BATTERY_REPORT_SIZE))
		power_supply_changed(drvdata->battery);

	return 0;
}