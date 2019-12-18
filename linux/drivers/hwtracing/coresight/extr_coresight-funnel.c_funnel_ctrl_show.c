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
typedef  int u32 ;
struct funnel_drvdata {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct funnel_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int get_funnel_ctrl_hw (struct funnel_drvdata*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t funnel_ctrl_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	u32 val;
	struct funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);

	pm_runtime_get_sync(dev->parent);

	val = get_funnel_ctrl_hw(drvdata);

	pm_runtime_put(dev->parent);

	return sprintf(buf, "%#x\n", val);
}