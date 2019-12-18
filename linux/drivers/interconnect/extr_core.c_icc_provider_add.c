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
struct icc_provider {int /*<<< orphan*/  dev; int /*<<< orphan*/  provider_list; int /*<<< orphan*/  nodes; int /*<<< orphan*/  xlate; int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  icc_lock ; 
 int /*<<< orphan*/  icc_providers ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int icc_provider_add(struct icc_provider *provider)
{
	if (WARN_ON(!provider->set))
		return -EINVAL;
	if (WARN_ON(!provider->xlate))
		return -EINVAL;

	mutex_lock(&icc_lock);

	INIT_LIST_HEAD(&provider->nodes);
	list_add_tail(&provider->provider_list, &icc_providers);

	mutex_unlock(&icc_lock);

	dev_dbg(provider->dev, "interconnect provider added to topology\n");

	return 0;
}