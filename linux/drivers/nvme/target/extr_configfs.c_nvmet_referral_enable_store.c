#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvmet_port {int dummy; } ;
struct config_item {TYPE_1__* ci_parent; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {struct config_item* ci_parent; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  nvmet_referral_disable (struct nvmet_port*,struct nvmet_port*) ; 
 int /*<<< orphan*/  nvmet_referral_enable (struct nvmet_port*,struct nvmet_port*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 scalar_t__ strtobool (char const*,int*) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_referral_enable_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_port *parent = to_nvmet_port(item->ci_parent->ci_parent);
	struct nvmet_port *port = to_nvmet_port(item);
	bool enable;

	if (strtobool(page, &enable))
		goto inval;

	if (enable)
		nvmet_referral_enable(parent, port);
	else
		nvmet_referral_disable(parent, port);

	return count;
inval:
	pr_err("Invalid value '%s' for enable\n", page);
	return -EINVAL;
}