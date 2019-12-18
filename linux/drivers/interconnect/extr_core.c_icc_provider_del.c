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
struct icc_provider {int /*<<< orphan*/  provider_list; int /*<<< orphan*/  nodes; scalar_t__ users; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  icc_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

int icc_provider_del(struct icc_provider *provider)
{
	mutex_lock(&icc_lock);
	if (provider->users) {
		pr_warn("interconnect provider still has %d users\n",
			provider->users);
		mutex_unlock(&icc_lock);
		return -EBUSY;
	}

	if (!list_empty(&provider->nodes)) {
		pr_warn("interconnect provider still has nodes\n");
		mutex_unlock(&icc_lock);
		return -EBUSY;
	}

	list_del(&provider->provider_list);
	mutex_unlock(&icc_lock);

	return 0;
}