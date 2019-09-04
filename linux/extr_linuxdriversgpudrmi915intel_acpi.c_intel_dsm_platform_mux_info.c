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
struct TYPE_6__ {int /*<<< orphan*/ * pointer; } ;
struct TYPE_5__ {scalar_t__ value; } ;
struct TYPE_4__ {int count; union acpi_object* elements; } ;
union acpi_object {TYPE_3__ buffer; TYPE_2__ integer; TYPE_1__ package; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  INTEL_DSM_FN_PLATFORM_MUX_INFO ; 
 int /*<<< orphan*/  INTEL_DSM_REVISION_ID ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dsm_guid ; 
 unsigned long long intel_dsm_mux_type (int /*<<< orphan*/ ) ; 
 unsigned long long intel_dsm_port_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dsm_platform_mux_info(acpi_handle dhandle)
{
	int i;
	union acpi_object *pkg, *connector_count;

	pkg = acpi_evaluate_dsm_typed(dhandle, &intel_dsm_guid,
			INTEL_DSM_REVISION_ID, INTEL_DSM_FN_PLATFORM_MUX_INFO,
			NULL, ACPI_TYPE_PACKAGE);
	if (!pkg) {
		DRM_DEBUG_DRIVER("failed to evaluate _DSM\n");
		return;
	}

	connector_count = &pkg->package.elements[0];
	DRM_DEBUG_DRIVER("MUX info connectors: %lld\n",
		  (unsigned long long)connector_count->integer.value);
	for (i = 1; i < pkg->package.count; i++) {
		union acpi_object *obj = &pkg->package.elements[i];
		union acpi_object *connector_id = &obj->package.elements[0];
		union acpi_object *info = &obj->package.elements[1];
		DRM_DEBUG_DRIVER("Connector id: 0x%016llx\n",
			  (unsigned long long)connector_id->integer.value);
		DRM_DEBUG_DRIVER("  port id: %s\n",
		       intel_dsm_port_name(info->buffer.pointer[0]));
		DRM_DEBUG_DRIVER("  display mux info: %s\n",
		       intel_dsm_mux_type(info->buffer.pointer[1]));
		DRM_DEBUG_DRIVER("  aux/dc mux info: %s\n",
		       intel_dsm_mux_type(info->buffer.pointer[2]));
		DRM_DEBUG_DRIVER("  hpd mux info: %s\n",
		       intel_dsm_mux_type(info->buffer.pointer[3]));
	}

	ACPI_FREE(pkg);
}