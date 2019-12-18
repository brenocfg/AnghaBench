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
 char* hmc_network ; 
 int /*<<< orphan*/  sclp_ocf_lock ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t hmc_network_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *page)
{
	int rc;

	spin_lock_irq(&sclp_ocf_lock);
	rc = snprintf(page, PAGE_SIZE, "%s\n", hmc_network);
	spin_unlock_irq(&sclp_ocf_lock);
	return rc;
}