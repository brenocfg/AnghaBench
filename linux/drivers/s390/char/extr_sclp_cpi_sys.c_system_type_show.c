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
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_cpi_mutex ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 char* system_type ; 

__attribute__((used)) static ssize_t system_type_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *page)
{
	int rc;

	mutex_lock(&sclp_cpi_mutex);
	rc = snprintf(page, PAGE_SIZE, "%s\n", system_type);
	mutex_unlock(&sclp_cpi_mutex);
	return rc;
}