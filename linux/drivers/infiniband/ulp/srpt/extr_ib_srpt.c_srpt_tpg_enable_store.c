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
struct srpt_port {int /*<<< orphan*/  mutex; } ;
struct se_portal_group {int dummy; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  srpt_set_enabled (struct srpt_port*,unsigned long) ; 
 struct srpt_port* srpt_tpg_to_sport (struct se_portal_group*) ; 
 struct se_portal_group* to_tpg (struct config_item*) ; 

__attribute__((used)) static ssize_t srpt_tpg_enable_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_portal_group *se_tpg = to_tpg(item);
	struct srpt_port *sport = srpt_tpg_to_sport(se_tpg);
	unsigned long tmp;
	int ret;

	ret = kstrtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract srpt_tpg_store_enable\n");
		return -EINVAL;
	}

	if ((tmp != 0) && (tmp != 1)) {
		pr_err("Illegal value for srpt_tpg_store_enable: %lu\n", tmp);
		return -EINVAL;
	}

	mutex_lock(&sport->mutex);
	srpt_set_enabled(sport, tmp);
	mutex_unlock(&sport->mutex);

	return count;
}