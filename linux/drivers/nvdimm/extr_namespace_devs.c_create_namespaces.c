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
struct nd_region {int ndr_mappings; struct nd_mapping* mapping; } ;
struct nd_mapping {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct device** scan_labels (struct nd_region*) ; 

__attribute__((used)) static struct device **create_namespaces(struct nd_region *nd_region)
{
	struct nd_mapping *nd_mapping;
	struct device **devs;
	int i;

	if (nd_region->ndr_mappings == 0)
		return NULL;

	/* lock down all mappings while we scan labels */
	for (i = 0; i < nd_region->ndr_mappings; i++) {
		nd_mapping = &nd_region->mapping[i];
		mutex_lock_nested(&nd_mapping->lock, i);
	}

	devs = scan_labels(nd_region);

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		int reverse = nd_region->ndr_mappings - 1 - i;

		nd_mapping = &nd_region->mapping[reverse];
		mutex_unlock(&nd_mapping->lock);
	}

	return devs;
}