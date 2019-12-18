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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ads7846 {int disabled; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct ads7846* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t ads7846_disable_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct ads7846 *ts = dev_get_drvdata(dev);

	return sprintf(buf, "%u\n", ts->disabled);
}