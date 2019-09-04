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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  set_lid_wake_behavior (int) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static ssize_t lid_wake_on_close_store(struct kobject *s,
				       struct kobj_attribute *attr,
				       const char *buf, size_t n)
{
	unsigned int val;

	if (sscanf(buf, "%u", &val) != 1)
		return -EINVAL;

	set_lid_wake_behavior(!!val);

	return n;
}