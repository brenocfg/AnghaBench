#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct radeon_crtc {size_t crtc_id; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {size_t ucCRTC; int ucBlanking; } ;
typedef  TYPE_2__ BLANK_CRTC_PS_ALLOCATION ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 int /*<<< orphan*/  BlankCRTC ; 
 int /*<<< orphan*/  COMMAND ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/ * vga_control_regs ; 

__attribute__((used)) static void atombios_blank_crtc(struct drm_crtc *crtc, int state)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	int index = GetIndexIntoMasterTable(COMMAND, BlankCRTC);
	BLANK_CRTC_PS_ALLOCATION args;
	u32 vga_control = 0;

	memset(&args, 0, sizeof(args));

	if (ASIC_IS_DCE8(rdev)) {
		vga_control = RREG32(vga_control_regs[radeon_crtc->crtc_id]);
		WREG32(vga_control_regs[radeon_crtc->crtc_id], vga_control | 1);
	}

	args.ucCRTC = radeon_crtc->crtc_id;
	args.ucBlanking = state;

	atom_execute_table(rdev->mode_info.atom_context, index, (uint32_t *)&args);

	if (ASIC_IS_DCE8(rdev)) {
		WREG32(vga_control_regs[radeon_crtc->crtc_id], vga_control);
	}
}