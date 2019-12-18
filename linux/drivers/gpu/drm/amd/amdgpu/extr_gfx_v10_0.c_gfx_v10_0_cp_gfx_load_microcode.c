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
struct TYPE_2__ {int /*<<< orphan*/  ce_fw; int /*<<< orphan*/  pfp_fw; int /*<<< orphan*/  me_fw; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_1__ gfx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_gfx_enable (struct amdgpu_device*,int) ; 
 int gfx_v10_0_cp_gfx_load_ce_microcode (struct amdgpu_device*) ; 
 int gfx_v10_0_cp_gfx_load_me_microcode (struct amdgpu_device*) ; 
 int gfx_v10_0_cp_gfx_load_pfp_microcode (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v10_0_cp_gfx_load_microcode(struct amdgpu_device *adev)
{
	int r;

	if (!adev->gfx.me_fw || !adev->gfx.pfp_fw || !adev->gfx.ce_fw)
		return -EINVAL;

	gfx_v10_0_cp_gfx_enable(adev, false);

	r = gfx_v10_0_cp_gfx_load_pfp_microcode(adev);
	if (r) {
		dev_err(adev->dev, "(%d) failed to load pfp fw\n", r);
		return r;
	}

	r = gfx_v10_0_cp_gfx_load_ce_microcode(adev);
	if (r) {
		dev_err(adev->dev, "(%d) failed to load ce fw\n", r);
		return r;
	}

	r = gfx_v10_0_cp_gfx_load_me_microcode(adev);
	if (r) {
		dev_err(adev->dev, "(%d) failed to load me fw\n", r);
		return r;
	}

	return 0;
}