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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dev_pm_opp_find_and_remove_table (struct device*) ; 

void dev_pm_opp_of_remove_table(struct device *dev)
{
	_dev_pm_opp_find_and_remove_table(dev);
}