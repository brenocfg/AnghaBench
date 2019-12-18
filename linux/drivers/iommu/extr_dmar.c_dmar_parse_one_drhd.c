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
struct dmar_drhd_unit {int include_all; scalar_t__ devices_cnt; int /*<<< orphan*/ * devices; int /*<<< orphan*/  segment; int /*<<< orphan*/  reg_base_addr; void* hdr; } ;
struct acpi_dmar_header {scalar_t__ length; } ;
struct TYPE_2__ {int length; } ;
struct acpi_dmar_hardware_unit {int flags; TYPE_1__ header; int /*<<< orphan*/  segment; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int alloc_iommu (struct dmar_drhd_unit*) ; 
 int /*<<< orphan*/ * dmar_alloc_dev_scope (void*,void*,scalar_t__*) ; 
 struct dmar_drhd_unit* dmar_find_dmaru (struct acpi_dmar_hardware_unit*) ; 
 int /*<<< orphan*/  dmar_free_dev_scope (int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  dmar_register_drhd_unit (struct dmar_drhd_unit*) ; 
 int /*<<< orphan*/  kfree (struct dmar_drhd_unit*) ; 
 struct dmar_drhd_unit* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct acpi_dmar_header*,scalar_t__) ; 

__attribute__((used)) static int dmar_parse_one_drhd(struct acpi_dmar_header *header, void *arg)
{
	struct acpi_dmar_hardware_unit *drhd;
	struct dmar_drhd_unit *dmaru;
	int ret;

	drhd = (struct acpi_dmar_hardware_unit *)header;
	dmaru = dmar_find_dmaru(drhd);
	if (dmaru)
		goto out;

	dmaru = kzalloc(sizeof(*dmaru) + header->length, GFP_KERNEL);
	if (!dmaru)
		return -ENOMEM;

	/*
	 * If header is allocated from slab by ACPI _DSM method, we need to
	 * copy the content because the memory buffer will be freed on return.
	 */
	dmaru->hdr = (void *)(dmaru + 1);
	memcpy(dmaru->hdr, header, header->length);
	dmaru->reg_base_addr = drhd->address;
	dmaru->segment = drhd->segment;
	dmaru->include_all = drhd->flags & 0x1; /* BIT0: INCLUDE_ALL */
	dmaru->devices = dmar_alloc_dev_scope((void *)(drhd + 1),
					      ((void *)drhd) + drhd->header.length,
					      &dmaru->devices_cnt);
	if (dmaru->devices_cnt && dmaru->devices == NULL) {
		kfree(dmaru);
		return -ENOMEM;
	}

	ret = alloc_iommu(dmaru);
	if (ret) {
		dmar_free_dev_scope(&dmaru->devices,
				    &dmaru->devices_cnt);
		kfree(dmaru);
		return ret;
	}
	dmar_register_drhd_unit(dmaru);

out:
	if (arg)
		(*(int *)arg)++;

	return 0;
}