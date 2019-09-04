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
typedef  int s8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__ ams_info ; 
 int /*<<< orphan*/  ams_sensors (int*,int*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static ssize_t ams_show_current(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	s8 x, y, z;

	mutex_lock(&ams_info.lock);
	ams_sensors(&x, &y, &z);
	mutex_unlock(&ams_info.lock);

	return snprintf(buf, PAGE_SIZE, "%d %d %d\n", x, y, z);
}