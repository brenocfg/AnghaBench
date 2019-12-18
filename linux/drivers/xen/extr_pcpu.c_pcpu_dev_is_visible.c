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
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct device {scalar_t__ id; } ;
struct attribute {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static umode_t pcpu_dev_is_visible(struct kobject *kobj,
				   struct attribute *attr, int idx)
{
	struct device *dev = kobj_to_dev(kobj);
	/*
	 * Xen never offline cpu0 due to several restrictions
	 * and assumptions. This basically doesn't add a sys control
	 * to user, one cannot attempt to offline BSP.
	 */
	return dev->id ? attr->mode : 0;
}