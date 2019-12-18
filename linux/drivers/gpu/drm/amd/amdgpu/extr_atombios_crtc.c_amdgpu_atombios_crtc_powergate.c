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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct amdgpu_crtc {int /*<<< orphan*/  crtc_id; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {int ucEnable; int /*<<< orphan*/  ucDispPipeId; } ;
typedef  TYPE_2__ ENABLE_DISP_POWER_GATING_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  EnableDispPowerGating ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

void amdgpu_atombios_crtc_powergate(struct drm_crtc *crtc, int state)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	int index = GetIndexIntoMasterTable(COMMAND, EnableDispPowerGating);
	ENABLE_DISP_POWER_GATING_PS_ALLOCATION args;

	memset(&args, 0, sizeof(args));

	args.ucDispPipeId = amdgpu_crtc->crtc_id;
	args.ucEnable = state;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);
}