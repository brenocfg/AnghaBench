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
struct TYPE_2__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  size_t u16 ;
struct atcs_verify_interface {int /*<<< orphan*/  function_bits; int /*<<< orphan*/  version; } ;
struct amdgpu_atcs {int /*<<< orphan*/  functions; } ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ATCS_FUNCTION_VERIFY_INTERFACE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*,size_t) ; 
 int EINVAL ; 
 int EIO ; 
 union acpi_object* amdgpu_atcs_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atcs_parse_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atcs_verify_interface*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atcs_verify_interface*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 

__attribute__((used)) static int amdgpu_atcs_verify_interface(acpi_handle handle,
					struct amdgpu_atcs *atcs)
{
	union acpi_object *info;
	struct atcs_verify_interface output;
	size_t size;
	int err = 0;

	info = amdgpu_atcs_call(handle, ATCS_FUNCTION_VERIFY_INTERFACE, NULL);
	if (!info)
		return -EIO;

	memset(&output, 0, sizeof(output));

	size = *(u16 *) info->buffer.pointer;
	if (size < 8) {
		DRM_INFO("ATCS buffer is too small: %zu\n", size);
		err = -EINVAL;
		goto out;
	}
	size = min(sizeof(output), size);

	memcpy(&output, info->buffer.pointer, size);

	/* TODO: check version? */
	DRM_DEBUG_DRIVER("ATCS version %u\n", output.version);

	amdgpu_atcs_parse_functions(&atcs->functions, output.function_bits);

out:
	kfree(info);
	return err;
}