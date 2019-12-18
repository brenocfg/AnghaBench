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
struct nvme_ns_head {int /*<<< orphan*/ * current_path; int /*<<< orphan*/  list; } ;
struct nvme_ns {scalar_t__ ana_state; } ;

/* Variables and functions */
 scalar_t__ NVME_ANA_NONOPTIMIZED ; 
 scalar_t__ NVME_ANA_OPTIMIZED ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 struct nvme_ns* nvme_next_ns (struct nvme_ns_head*,struct nvme_ns*) ; 
 scalar_t__ nvme_path_is_disabled (struct nvme_ns*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nvme_ns*) ; 

__attribute__((used)) static struct nvme_ns *nvme_round_robin_path(struct nvme_ns_head *head,
		int node, struct nvme_ns *old)
{
	struct nvme_ns *ns, *found, *fallback = NULL;

	if (list_is_singular(&head->list)) {
		if (nvme_path_is_disabled(old))
			return NULL;
		return old;
	}

	for (ns = nvme_next_ns(head, old);
	     ns != old;
	     ns = nvme_next_ns(head, ns)) {
		if (nvme_path_is_disabled(ns))
			continue;

		if (ns->ana_state == NVME_ANA_OPTIMIZED) {
			found = ns;
			goto out;
		}
		if (ns->ana_state == NVME_ANA_NONOPTIMIZED)
			fallback = ns;
	}

	if (!fallback)
		return NULL;
	found = fallback;
out:
	rcu_assign_pointer(head->current_path[node], found);
	return found;
}