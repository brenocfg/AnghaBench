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
struct pasid_table {struct pasid_entry* table; } ;
struct pasid_entry {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int intel_pasid_get_dev_max_id (struct device*) ; 
 struct pasid_table* intel_pasid_get_table (struct device*) ; 

struct pasid_entry *intel_pasid_get_entry(struct device *dev, int pasid)
{
	struct pasid_table *pasid_table;
	struct pasid_entry *entries;

	pasid_table = intel_pasid_get_table(dev);
	if (WARN_ON(!pasid_table || pasid < 0 ||
		    pasid >= intel_pasid_get_dev_max_id(dev)))
		return NULL;

	entries = pasid_table->table;

	return &entries[pasid];
}