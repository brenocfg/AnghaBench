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
struct dmar_domain {int flags; int has_iotlb_device; int /*<<< orphan*/  devices; int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct dmar_domain* alloc_domain_mem () ; 
 int /*<<< orphan*/  memset (struct dmar_domain*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dmar_domain *alloc_domain(int flags)
{
	struct dmar_domain *domain;

	domain = alloc_domain_mem();
	if (!domain)
		return NULL;

	memset(domain, 0, sizeof(*domain));
	domain->nid = NUMA_NO_NODE;
	domain->flags = flags;
	domain->has_iotlb_device = false;
	INIT_LIST_HEAD(&domain->devices);

	return domain;
}