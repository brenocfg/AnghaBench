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
struct TYPE_2__ {int /*<<< orphan*/ * ta_fw; int /*<<< orphan*/ * asd_fw; int /*<<< orphan*/ * sos_fw; } ;
struct amdgpu_device {TYPE_1__ psp; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psp_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	release_firmware(adev->psp.sos_fw);
	adev->psp.sos_fw = NULL;
	release_firmware(adev->psp.asd_fw);
	adev->psp.asd_fw = NULL;
	if (adev->psp.ta_fw) {
		release_firmware(adev->psp.ta_fw);
		adev->psp.ta_fw = NULL;
	}
	return 0;
}