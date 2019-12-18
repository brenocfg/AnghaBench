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
struct nvmet_subsys {int /*<<< orphan*/  lock; } ;
struct nvmet_ns {int /*<<< orphan*/  device_path; scalar_t__ enabled; struct nvmet_subsys* subsys; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t strcspn (char const*,char*) ; 
 struct nvmet_ns* to_nvmet_ns (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_ns_device_path_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_ns *ns = to_nvmet_ns(item);
	struct nvmet_subsys *subsys = ns->subsys;
	size_t len;
	int ret;

	mutex_lock(&subsys->lock);
	ret = -EBUSY;
	if (ns->enabled)
		goto out_unlock;

	ret = -EINVAL;
	len = strcspn(page, "\n");
	if (!len)
		goto out_unlock;

	kfree(ns->device_path);
	ret = -ENOMEM;
	ns->device_path = kstrndup(page, len, GFP_KERNEL);
	if (!ns->device_path)
		goto out_unlock;

	mutex_unlock(&subsys->lock);
	return count;

out_unlock:
	mutex_unlock(&subsys->lock);
	return ret;
}