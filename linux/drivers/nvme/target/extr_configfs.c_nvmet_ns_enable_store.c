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
struct nvmet_ns {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvmet_ns_disable (struct nvmet_ns*) ; 
 int nvmet_ns_enable (struct nvmet_ns*) ; 
 scalar_t__ strtobool (char const*,int*) ; 
 struct nvmet_ns* to_nvmet_ns (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_ns_enable_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_ns *ns = to_nvmet_ns(item);
	bool enable;
	int ret = 0;

	if (strtobool(page, &enable))
		return -EINVAL;

	if (enable)
		ret = nvmet_ns_enable(ns);
	else
		nvmet_ns_disable(ns);

	return ret ? ret : count;
}