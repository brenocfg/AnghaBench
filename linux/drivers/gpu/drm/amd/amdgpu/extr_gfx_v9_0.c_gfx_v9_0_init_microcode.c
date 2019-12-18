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
struct amdgpu_device {int asic_type; int rev_id; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int gfx_v9_0_init_cp_compute_microcode (struct amdgpu_device*,char const*) ; 
 int gfx_v9_0_init_cp_gfx_microcode (struct amdgpu_device*,char const*) ; 
 int gfx_v9_0_init_rlc_microcode (struct amdgpu_device*,char const*) ; 

__attribute__((used)) static int gfx_v9_0_init_microcode(struct amdgpu_device *adev)
{
	const char *chip_name;
	int r;

	DRM_DEBUG("\n");

	switch (adev->asic_type) {
	case CHIP_VEGA10:
		chip_name = "vega10";
		break;
	case CHIP_VEGA12:
		chip_name = "vega12";
		break;
	case CHIP_VEGA20:
		chip_name = "vega20";
		break;
	case CHIP_RAVEN:
		if (adev->rev_id >= 8)
			chip_name = "raven2";
		else if (adev->pdev->device == 0x15d8)
			chip_name = "picasso";
		else
			chip_name = "raven";
		break;
	case CHIP_ARCTURUS:
		chip_name = "arcturus";
		break;
	case CHIP_RENOIR:
		chip_name = "renoir";
		break;
	default:
		BUG();
	}

	/* No CPG in Arcturus */
	if (adev->asic_type != CHIP_ARCTURUS) {
		r = gfx_v9_0_init_cp_gfx_microcode(adev, chip_name);
		if (r)
			return r;
	}

	r = gfx_v9_0_init_rlc_microcode(adev, chip_name);
	if (r)
		return r;

	r = gfx_v9_0_init_cp_compute_microcode(adev, chip_name);
	if (r)
		return r;

	return r;
}