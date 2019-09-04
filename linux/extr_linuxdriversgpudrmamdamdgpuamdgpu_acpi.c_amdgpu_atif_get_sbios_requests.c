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
struct atif_sbios_requests {int /*<<< orphan*/  pending; } ;
struct amdgpu_atif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 union acpi_object* amdgpu_atif_call (struct amdgpu_atif*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atif_sbios_requests*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atif_sbios_requests*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 

__attribute__((used)) static int amdgpu_atif_get_sbios_requests(struct amdgpu_atif *atif,
					  struct atif_sbios_requests *req)
{
	union acpi_object *info;
	size_t size;
	int count = 0;

	info = amdgpu_atif_call(atif, ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS,
				NULL);
	if (!info)
		return -EIO;

	size = *(u16 *)info->buffer.pointer;
	if (size < 0xd) {
		count = -EINVAL;
		goto out;
	}
	memset(req, 0, sizeof(*req));

	size = min(sizeof(*req), size);
	memcpy(req, info->buffer.pointer, size);
	DRM_DEBUG_DRIVER("SBIOS pending requests: %#x\n", req->pending);

	count = hweight32(req->pending);

out:
	kfree(info);
	return count;
}