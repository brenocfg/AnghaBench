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
struct pasid_table_opaque {scalar_t__ segment; scalar_t__ bus; scalar_t__ devfn; scalar_t__* pasid_table; } ;
struct device_domain_info {scalar_t__ bus; scalar_t__ devfn; scalar_t__ pasid_table; TYPE_1__* iommu; } ;
struct TYPE_2__ {scalar_t__ segment; } ;

/* Variables and functions */

__attribute__((used)) static int search_pasid_table(struct device_domain_info *info, void *opaque)
{
	struct pasid_table_opaque *data = opaque;

	if (info->iommu->segment == data->segment &&
	    info->bus == data->bus &&
	    info->devfn == data->devfn &&
	    info->pasid_table) {
		*data->pasid_table = info->pasid_table;
		return 1;
	}

	return 0;
}