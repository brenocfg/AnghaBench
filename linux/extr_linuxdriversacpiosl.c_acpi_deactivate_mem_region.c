#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ space_id; int flags; union acpi_operand_object* handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* setup ) (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  region_context; } ;
union acpi_operand_object {TYPE_3__ region; TYPE_2__ address_space; TYPE_1__ extra; } ;
typedef  int /*<<< orphan*/  u32 ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct acpi_mem_space_context {scalar_t__ address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_REGION_DEACTIVATE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_SETUP_COMPLETE ; 
 union acpi_operand_object* acpi_ns_get_attached_object (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  stub1 (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static acpi_status acpi_deactivate_mem_region(acpi_handle handle, u32 level,
					      void *_res, void **return_value)
{
	struct acpi_mem_space_context **mem_ctx;
	union acpi_operand_object *handler_obj;
	union acpi_operand_object *region_obj2;
	union acpi_operand_object *region_obj;
	struct resource *res = _res;
	acpi_status status;

	region_obj = acpi_ns_get_attached_object(handle);
	if (!region_obj)
		return AE_OK;

	handler_obj = region_obj->region.handler;
	if (!handler_obj)
		return AE_OK;

	if (region_obj->region.space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY)
		return AE_OK;

	if (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE))
		return AE_OK;

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	if (!region_obj2)
		return AE_OK;

	mem_ctx = (void *)&region_obj2->extra.region_context;

	if (!(mem_ctx[0]->address >= res->start &&
	      mem_ctx[0]->address < res->end))
		return AE_OK;

	status = handler_obj->address_space.setup(region_obj,
						  ACPI_REGION_DEACTIVATE,
						  NULL, (void **)mem_ctx);
	if (ACPI_SUCCESS(status))
		region_obj->region.flags &= ~(AOPOBJ_SETUP_COMPLETE);

	return status;
}