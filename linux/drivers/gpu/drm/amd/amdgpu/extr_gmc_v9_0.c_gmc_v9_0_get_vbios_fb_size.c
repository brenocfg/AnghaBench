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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int real_vram_size; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gmc; } ;

/* Variables and functions */
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  D1VGA_CONTROL ; 
 int /*<<< orphan*/  D1VGA_MODE_ENABLE ; 
 int /*<<< orphan*/  DCE ; 
 int /*<<< orphan*/  HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION ; 
 int /*<<< orphan*/  PRI_VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  PRI_VIEWPORT_WIDTH ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCL0_VIEWPORT_SIZE ; 
 int /*<<< orphan*/  VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  VIEWPORT_WIDTH ; 
 scalar_t__ gmc_v9_0_keep_stolen_memory (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmD1VGA_CONTROL ; 
 int /*<<< orphan*/  mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION ; 
 int /*<<< orphan*/  mmSCL0_VIEWPORT_SIZE ; 

__attribute__((used)) static unsigned gmc_v9_0_get_vbios_fb_size(struct amdgpu_device *adev)
{
	u32 d1vga_control;
	unsigned size;

	/*
	 * TODO Remove once GART corruption is resolved
	 * Check related code in gmc_v9_0_sw_fini
	 * */
	if (gmc_v9_0_keep_stolen_memory(adev))
		return 9 * 1024 * 1024;

	d1vga_control = RREG32_SOC15(DCE, 0, mmD1VGA_CONTROL);
	if (REG_GET_FIELD(d1vga_control, D1VGA_CONTROL, D1VGA_MODE_ENABLE)) {
		size = 9 * 1024 * 1024; /* reserve 8MB for vga emulator and 1 MB for FB */
	} else {
		u32 viewport;

		switch (adev->asic_type) {
		case CHIP_RAVEN:
		case CHIP_RENOIR:
			viewport = RREG32_SOC15(DCE, 0, mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION);
			size = (REG_GET_FIELD(viewport,
					      HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION, PRI_VIEWPORT_HEIGHT) *
				REG_GET_FIELD(viewport,
					      HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION, PRI_VIEWPORT_WIDTH) *
				4);
			break;
		case CHIP_VEGA10:
		case CHIP_VEGA12:
		case CHIP_VEGA20:
		default:
			viewport = RREG32_SOC15(DCE, 0, mmSCL0_VIEWPORT_SIZE);
			size = (REG_GET_FIELD(viewport, SCL0_VIEWPORT_SIZE, VIEWPORT_HEIGHT) *
				REG_GET_FIELD(viewport, SCL0_VIEWPORT_SIZE, VIEWPORT_WIDTH) *
				4);
			break;
		}
	}
	/* return 0 if the pre-OS buffer uses up most of vram */
	if ((adev->gmc.real_vram_size - size) < (8 * 1024 * 1024))
		return 0;

	return size;
}