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
struct pasid_table {int /*<<< orphan*/  dev; } ;
struct device_domain_info {int /*<<< orphan*/  table; struct pasid_table* pasid_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
device_attach_pasid_table(struct device_domain_info *info,
			  struct pasid_table *pasid_table)
{
	info->pasid_table = pasid_table;
	list_add(&info->table, &pasid_table->dev);
}