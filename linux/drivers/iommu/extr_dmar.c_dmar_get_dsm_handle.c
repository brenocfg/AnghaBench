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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  void* acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DMAR_DSM_FUNC_DRHD ; 
 scalar_t__ dmar_detect_dsm (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status dmar_get_dsm_handle(acpi_handle handle, u32 lvl,
				       void *context, void **retval)
{
	acpi_handle *phdl = retval;

	if (dmar_detect_dsm(handle, DMAR_DSM_FUNC_DRHD)) {
		*phdl = handle;
		return AE_CTRL_TERMINATE;
	}

	return AE_OK;
}