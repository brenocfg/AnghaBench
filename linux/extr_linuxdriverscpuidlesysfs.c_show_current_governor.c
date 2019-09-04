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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 TYPE_1__* cpuidle_curr_governor ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t show_current_governor(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	ssize_t ret;

	mutex_lock(&cpuidle_lock);
	if (cpuidle_curr_governor)
		ret = sprintf(buf, "%s\n", cpuidle_curr_governor->name);
	else
		ret = sprintf(buf, "none\n");
	mutex_unlock(&cpuidle_lock);

	return ret;
}