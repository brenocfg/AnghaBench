#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {char* name; int start; int end; struct resource* sibling; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int minimum; int maximum; } ;
struct TYPE_9__ {TYPE_3__ address; } ;
struct TYPE_6__ {int minimum; int maximum; } ;
struct TYPE_7__ {TYPE_1__ address; } ;
struct TYPE_10__ {TYPE_4__ address64; TYPE_2__ address32; } ;
struct acpi_resource {int type; TYPE_5__ data; } ;
typedef  int resource_size_t ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_ADDRESS32 129 
#define  ACPI_RESOURCE_TYPE_ADDRESS64 128 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int VTPM_BASE_ADDRESS ; 
 struct resource* hyperv_mmio ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status vmbus_walk_resources(struct acpi_resource *res, void *ctx)
{
	resource_size_t start = 0;
	resource_size_t end = 0;
	struct resource *new_res;
	struct resource **old_res = &hyperv_mmio;
	struct resource **prev_res = NULL;

	switch (res->type) {

	/*
	 * "Address" descriptors are for bus windows. Ignore
	 * "memory" descriptors, which are for registers on
	 * devices.
	 */
	case ACPI_RESOURCE_TYPE_ADDRESS32:
		start = res->data.address32.address.minimum;
		end = res->data.address32.address.maximum;
		break;

	case ACPI_RESOURCE_TYPE_ADDRESS64:
		start = res->data.address64.address.minimum;
		end = res->data.address64.address.maximum;
		break;

	default:
		/* Unused resource type */
		return AE_OK;

	}
	/*
	 * Ignore ranges that are below 1MB, as they're not
	 * necessary or useful here.
	 */
	if (end < 0x100000)
		return AE_OK;

	new_res = kzalloc(sizeof(*new_res), GFP_ATOMIC);
	if (!new_res)
		return AE_NO_MEMORY;

	/* If this range overlaps the virtual TPM, truncate it. */
	if (end > VTPM_BASE_ADDRESS && start < VTPM_BASE_ADDRESS)
		end = VTPM_BASE_ADDRESS;

	new_res->name = "hyperv mmio";
	new_res->flags = IORESOURCE_MEM;
	new_res->start = start;
	new_res->end = end;

	/*
	 * If two ranges are adjacent, merge them.
	 */
	do {
		if (!*old_res) {
			*old_res = new_res;
			break;
		}

		if (((*old_res)->end + 1) == new_res->start) {
			(*old_res)->end = new_res->end;
			kfree(new_res);
			break;
		}

		if ((*old_res)->start == new_res->end + 1) {
			(*old_res)->start = new_res->start;
			kfree(new_res);
			break;
		}

		if ((*old_res)->start > new_res->end) {
			new_res->sibling = *old_res;
			if (prev_res)
				(*prev_res)->sibling = new_res;
			*old_res = new_res;
			break;
		}

		prev_res = old_res;
		old_res = &(*old_res)->sibling;

	} while (1);

	return AE_OK;
}