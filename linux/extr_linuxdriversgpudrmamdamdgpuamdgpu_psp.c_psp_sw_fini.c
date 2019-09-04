#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * asd_fw; int /*<<< orphan*/ * sos_fw; } ;
struct TYPE_3__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_2__ psp; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psp_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP)
		return 0;

	release_firmware(adev->psp.sos_fw);
	adev->psp.sos_fw = NULL;
	release_firmware(adev->psp.asd_fw);
	adev->psp.asd_fw = NULL;
	return 0;
}