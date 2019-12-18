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
struct resource {int /*<<< orphan*/  start; } ;
struct nvdimm_bus {int dummy; } ;
struct nd_region_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  target_node; int /*<<< orphan*/  attr_groups; struct resource* res; } ;
typedef  int /*<<< orphan*/  ndr_desc ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ND_REGION_PAGEMAP ; 
 int /*<<< orphan*/  e820_pmem_region_attribute_groups ; 
 int /*<<< orphan*/  e820_range_to_nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nd_region_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvdimm_pmem_region_create (struct nvdimm_bus*,struct nd_region_desc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int e820_register_one(struct resource *res, void *data)
{
	struct nd_region_desc ndr_desc;
	struct nvdimm_bus *nvdimm_bus = data;

	memset(&ndr_desc, 0, sizeof(ndr_desc));
	ndr_desc.res = res;
	ndr_desc.attr_groups = e820_pmem_region_attribute_groups;
	ndr_desc.numa_node = e820_range_to_nid(res->start);
	ndr_desc.target_node = ndr_desc.numa_node;
	set_bit(ND_REGION_PAGEMAP, &ndr_desc.flags);
	if (!nvdimm_pmem_region_create(nvdimm_bus, &ndr_desc))
		return -ENXIO;
	return 0;
}