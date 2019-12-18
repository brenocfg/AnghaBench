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
 int cpi_req () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_cpi_mutex ; 

__attribute__((used)) static ssize_t set_store(struct kobject *kobj,
			 struct kobj_attribute *attr,
			 const char *buf, size_t len)
{
	int rc;

	mutex_lock(&sclp_cpi_mutex);
	rc = cpi_req();
	mutex_unlock(&sclp_cpi_mutex);
	if (rc)
		return rc;

	return len;
}