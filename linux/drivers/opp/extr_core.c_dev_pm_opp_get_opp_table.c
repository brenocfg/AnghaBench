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
struct opp_table {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct opp_table* _opp_get_opp_table (struct device*,int /*<<< orphan*/ ) ; 

struct opp_table *dev_pm_opp_get_opp_table(struct device *dev)
{
	return _opp_get_opp_table(dev, 0);
}