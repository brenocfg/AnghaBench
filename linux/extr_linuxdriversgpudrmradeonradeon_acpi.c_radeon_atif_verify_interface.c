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
struct radeon_atif {int /*<<< orphan*/  functions; int /*<<< orphan*/  notifications; } ;
struct atif_verify_interface {int /*<<< orphan*/  function_bits; int /*<<< orphan*/  notification_mask; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ATIF_FUNCTION_VERIFY_INTERFACE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*,size_t) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atif_verify_interface*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atif_verify_interface*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 
 union acpi_object* radeon_atif_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_atif_parse_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atif_parse_notification (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_atif_verify_interface(acpi_handle handle,
		struct radeon_atif *atif)
{
	union acpi_object *info;
	struct atif_verify_interface output;
	size_t size;
	int err = 0;

	info = radeon_atif_call(handle, ATIF_FUNCTION_VERIFY_INTERFACE, NULL);
	if (!info)
		return -EIO;

	memset(&output, 0, sizeof(output));

	size = *(u16 *) info->buffer.pointer;
	if (size < 12) {
		DRM_INFO("ATIF buffer is too small: %zu\n", size);
		err = -EINVAL;
		goto out;
	}
	size = min(sizeof(output), size);

	memcpy(&output, info->buffer.pointer, size);

	/* TODO: check version? */
	DRM_DEBUG_DRIVER("ATIF version %u\n", output.version);

	radeon_atif_parse_notification(&atif->notifications, output.notification_mask);
	radeon_atif_parse_functions(&atif->functions, output.function_bits);

out:
	kfree(info);
	return err;
}