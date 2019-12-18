#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_4__ buffer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct atcs_pref_req_output {int ret_val; } ;
struct atcs_pref_req_input {int size; int client_id; int /*<<< orphan*/  perf_req; int /*<<< orphan*/  req_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  valid_flags_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  pcie_perf_req; } ;
struct amdgpu_atcs {TYPE_1__ functions; } ;
struct amdgpu_device {TYPE_3__* pdev; struct amdgpu_atcs atcs; } ;
struct acpi_buffer {int length; struct atcs_pref_req_input* pointer; } ;
typedef  int /*<<< orphan*/  atcs_output ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_7__ {int devfn; TYPE_2__* bus; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATCS_ADVERTISE_CAPS ; 
 int /*<<< orphan*/  ATCS_FUNCTION_PCIE_PERFORMANCE_REQUEST ; 
 int /*<<< orphan*/  ATCS_PCIE_LINK_SPEED ; 
#define  ATCS_REQUEST_COMPLETE 130 
#define  ATCS_REQUEST_IN_PROGRESS 129 
#define  ATCS_REQUEST_REFUSED 128 
 int /*<<< orphan*/  ATCS_VALID_FLAGS_MASK ; 
 int /*<<< orphan*/  ATCS_WAIT_FOR_COMPLETION ; 
 int /*<<< orphan*/  DRM_INFO (char*,size_t) ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ amdgpu_acpi_pcie_notify_device_ready (struct amdgpu_device*) ; 
 union acpi_object* amdgpu_atcs_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atcs_pref_req_output*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atcs_pref_req_output*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 
 int /*<<< orphan*/  udelay (int) ; 

int amdgpu_acpi_pcie_performance_request(struct amdgpu_device *adev,
					 u8 perf_req, bool advertise)
{
	acpi_handle handle;
	union acpi_object *info;
	struct amdgpu_atcs *atcs = &adev->atcs;
	struct atcs_pref_req_input atcs_input;
	struct atcs_pref_req_output atcs_output;
	struct acpi_buffer params;
	size_t size;
	u32 retry = 3;

	if (amdgpu_acpi_pcie_notify_device_ready(adev))
		return -EINVAL;

	/* Get the device handle */
	handle = ACPI_HANDLE(&adev->pdev->dev);
	if (!handle)
		return -EINVAL;

	if (!atcs->functions.pcie_perf_req)
		return -EINVAL;

	atcs_input.size = sizeof(struct atcs_pref_req_input);
	/* client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	atcs_input.client_id = adev->pdev->devfn | (adev->pdev->bus->number << 8);
	atcs_input.valid_flags_mask = ATCS_VALID_FLAGS_MASK;
	atcs_input.flags = ATCS_WAIT_FOR_COMPLETION;
	if (advertise)
		atcs_input.flags |= ATCS_ADVERTISE_CAPS;
	atcs_input.req_type = ATCS_PCIE_LINK_SPEED;
	atcs_input.perf_req = perf_req;

	params.length = sizeof(struct atcs_pref_req_input);
	params.pointer = &atcs_input;

	while (retry--) {
		info = amdgpu_atcs_call(handle, ATCS_FUNCTION_PCIE_PERFORMANCE_REQUEST, &params);
		if (!info)
			return -EIO;

		memset(&atcs_output, 0, sizeof(atcs_output));

		size = *(u16 *) info->buffer.pointer;
		if (size < 3) {
			DRM_INFO("ATCS buffer is too small: %zu\n", size);
			kfree(info);
			return -EINVAL;
		}
		size = min(sizeof(atcs_output), size);

		memcpy(&atcs_output, info->buffer.pointer, size);

		kfree(info);

		switch (atcs_output.ret_val) {
		case ATCS_REQUEST_REFUSED:
		default:
			return -EINVAL;
		case ATCS_REQUEST_COMPLETE:
			return 0;
		case ATCS_REQUEST_IN_PROGRESS:
			udelay(10);
			break;
		}
	}

	return 0;
}