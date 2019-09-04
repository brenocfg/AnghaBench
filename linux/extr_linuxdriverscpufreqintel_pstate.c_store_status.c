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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pstate_driver_lock ; 
 int intel_pstate_update_status (char const*,int) ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_status(struct kobject *a, struct kobj_attribute *b,
			    const char *buf, size_t count)
{
	char *p = memchr(buf, '\n', count);
	int ret;

	mutex_lock(&intel_pstate_driver_lock);
	ret = intel_pstate_update_status(buf, p ? p - buf : count);
	mutex_unlock(&intel_pstate_driver_lock);

	return ret < 0 ? ret : count;
}