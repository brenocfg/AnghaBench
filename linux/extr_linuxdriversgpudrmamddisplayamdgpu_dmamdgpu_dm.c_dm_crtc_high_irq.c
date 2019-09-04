#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct common_irq_params {scalar_t__ irq_src; struct amdgpu_device* adev; } ;
struct amdgpu_device {int /*<<< orphan*/  ddev; } ;
struct amdgpu_crtc {int /*<<< orphan*/  base; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 scalar_t__ IRQ_TYPE_VBLANK ; 
 int /*<<< orphan*/  amdgpu_dm_crtc_handle_crc_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_handle_vblank (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_crtc* get_crtc_by_otg_inst (struct amdgpu_device*,scalar_t__) ; 

__attribute__((used)) static void dm_crtc_high_irq(void *interrupt_params)
{
	struct common_irq_params *irq_params = interrupt_params;
	struct amdgpu_device *adev = irq_params->adev;
	uint8_t crtc_index = 0;
	struct amdgpu_crtc *acrtc;

	acrtc = get_crtc_by_otg_inst(adev, irq_params->irq_src - IRQ_TYPE_VBLANK);

	if (acrtc)
		crtc_index = acrtc->crtc_id;

	drm_handle_vblank(adev->ddev, crtc_index);
	amdgpu_dm_crtc_handle_crc_irq(&acrtc->base);
}