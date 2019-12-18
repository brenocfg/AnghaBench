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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_cpi_mutex ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 unsigned long long system_level ; 

__attribute__((used)) static ssize_t system_level_show(struct kobject *kobj,
				 struct kobj_attribute *attr, char *page)
{
	unsigned long long level;

	mutex_lock(&sclp_cpi_mutex);
	level = system_level;
	mutex_unlock(&sclp_cpi_mutex);
	return snprintf(page, PAGE_SIZE, "%#018llx\n", level);
}