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
struct TYPE_2__ {int /*<<< orphan*/ * rlc_fw; int /*<<< orphan*/ * mec2_fw; int /*<<< orphan*/ * mec_fw; int /*<<< orphan*/ * ce_fw; int /*<<< orphan*/ * me_fw; int /*<<< orphan*/ * pfp_fw; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_v7_0_free_microcode(struct amdgpu_device *adev)
{
	release_firmware(adev->gfx.pfp_fw);
	adev->gfx.pfp_fw = NULL;
	release_firmware(adev->gfx.me_fw);
	adev->gfx.me_fw = NULL;
	release_firmware(adev->gfx.ce_fw);
	adev->gfx.ce_fw = NULL;
	release_firmware(adev->gfx.mec_fw);
	adev->gfx.mec_fw = NULL;
	release_firmware(adev->gfx.mec2_fw);
	adev->gfx.mec2_fw = NULL;
	release_firmware(adev->gfx.rlc_fw);
	adev->gfx.rlc_fw = NULL;
}