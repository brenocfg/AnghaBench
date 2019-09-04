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
struct stm_drvdata {unsigned long traceid; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct stm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t traceid_show(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	unsigned long val;
	struct stm_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->traceid;
	return sprintf(buf, "%#lx\n", val);
}