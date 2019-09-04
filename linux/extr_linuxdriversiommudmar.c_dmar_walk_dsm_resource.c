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
struct TYPE_2__ {int /*<<< orphan*/  length; scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
struct dmar_res_callback {void** arg; int /*<<< orphan*/ * cb; } ;
struct acpi_dmar_header {int dummy; } ;
typedef  int /*<<< orphan*/  dmar_res_handler_t ;
typedef  int /*<<< orphan*/  callback ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  ACPI_DMAR_TYPE_HARDWARE_AFFINITY 133 
#define  ACPI_DMAR_TYPE_HARDWARE_UNIT 132 
#define  ACPI_DMAR_TYPE_ROOT_ATS 131 
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
#define  DMAR_DSM_FUNC_ATSR 130 
#define  DMAR_DSM_FUNC_DRHD 129 
#define  DMAR_DSM_FUNC_RHSA 128 
 int /*<<< orphan*/  DMAR_DSM_REV_ID ; 
 int ENODEV ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_detect_dsm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_hp_guid ; 
 int dmar_walk_remapping_entries (struct acpi_dmar_header*,int /*<<< orphan*/ ,struct dmar_res_callback*) ; 
 int /*<<< orphan*/  memset (struct dmar_res_callback*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dmar_walk_dsm_resource(acpi_handle handle, int func,
				  dmar_res_handler_t handler, void *arg)
{
	int ret = -ENODEV;
	union acpi_object *obj;
	struct acpi_dmar_header *start;
	struct dmar_res_callback callback;
	static int res_type[] = {
		[DMAR_DSM_FUNC_DRHD] = ACPI_DMAR_TYPE_HARDWARE_UNIT,
		[DMAR_DSM_FUNC_ATSR] = ACPI_DMAR_TYPE_ROOT_ATS,
		[DMAR_DSM_FUNC_RHSA] = ACPI_DMAR_TYPE_HARDWARE_AFFINITY,
	};

	if (!dmar_detect_dsm(handle, func))
		return 0;

	obj = acpi_evaluate_dsm_typed(handle, &dmar_hp_guid, DMAR_DSM_REV_ID,
				      func, NULL, ACPI_TYPE_BUFFER);
	if (!obj)
		return -ENODEV;

	memset(&callback, 0, sizeof(callback));
	callback.cb[res_type[func]] = handler;
	callback.arg[res_type[func]] = arg;
	start = (struct acpi_dmar_header *)obj->buffer.pointer;
	ret = dmar_walk_remapping_entries(start, obj->buffer.length, &callback);

	ACPI_FREE(obj);

	return ret;
}