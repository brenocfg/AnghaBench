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
struct nvmet_subsys {int allow_any_host; int /*<<< orphan*/  hosts; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 int /*<<< orphan*/  nvmet_subsys_disc_changed (struct nvmet_subsys*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ strtobool (char const*,int*) ; 
 struct nvmet_subsys* to_subsys (struct config_item*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t nvmet_subsys_attr_allow_any_host_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_subsys *subsys = to_subsys(item);
	bool allow_any_host;
	int ret = 0;

	if (strtobool(page, &allow_any_host))
		return -EINVAL;

	down_write(&nvmet_config_sem);
	if (allow_any_host && !list_empty(&subsys->hosts)) {
		pr_err("Can't set allow_any_host when explicit hosts are set!\n");
		ret = -EINVAL;
		goto out_unlock;
	}

	if (subsys->allow_any_host != allow_any_host) {
		subsys->allow_any_host = allow_any_host;
		nvmet_subsys_disc_changed(subsys, NULL);
	}

out_unlock:
	up_write(&nvmet_config_sem);
	return ret ? ret : count;
}