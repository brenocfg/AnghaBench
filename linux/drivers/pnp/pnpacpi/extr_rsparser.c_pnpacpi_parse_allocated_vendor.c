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
typedef  scalar_t__ u64 ;
struct pnp_dev {int dummy; } ;
struct acpi_resource_vendor_typed {scalar_t__ byte_data; } ;
typedef  int /*<<< orphan*/  start ;
typedef  int /*<<< orphan*/  length ;

/* Variables and functions */
 int /*<<< orphan*/  hp_ccsr_uuid ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  pnp_add_mem_resource (struct pnp_dev*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vendor_resource_matches (struct pnp_dev*,struct acpi_resource_vendor_typed*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pnpacpi_parse_allocated_vendor(struct pnp_dev *dev,
				    struct acpi_resource_vendor_typed *vendor)
{
	if (vendor_resource_matches(dev, vendor, &hp_ccsr_uuid, 16)) {
		u64 start, length;

		memcpy(&start, vendor->byte_data, sizeof(start));
		memcpy(&length, vendor->byte_data + 8, sizeof(length));

		pnp_add_mem_resource(dev, start, start + length - 1, 0);
	}
}