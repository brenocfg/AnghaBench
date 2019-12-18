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
struct rc_scancode_filter {int mask; int data; } ;
struct rc_filter_attribute {scalar_t__ type; scalar_t__ mask; } ;
struct rc_dev {int /*<<< orphan*/  lock; struct rc_scancode_filter scancode_wakeup_filter; struct rc_scancode_filter scancode_filter; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ RC_FILTER_NORMAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct rc_dev* to_rc_dev (struct device*) ; 
 struct rc_filter_attribute* to_rc_filter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_filter(struct device *device,
			   struct device_attribute *attr,
			   char *buf)
{
	struct rc_dev *dev = to_rc_dev(device);
	struct rc_filter_attribute *fattr = to_rc_filter_attr(attr);
	struct rc_scancode_filter *filter;
	u32 val;

	mutex_lock(&dev->lock);

	if (fattr->type == RC_FILTER_NORMAL)
		filter = &dev->scancode_filter;
	else
		filter = &dev->scancode_wakeup_filter;

	if (fattr->mask)
		val = filter->mask;
	else
		val = filter->data;
	mutex_unlock(&dev->lock);

	return sprintf(buf, "%#x\n", val);
}