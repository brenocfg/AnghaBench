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
struct dc_interrupt_params {size_t irq_source; void* int_context; void* current_polarity; void* requested_polarity; int /*<<< orphan*/  member_0; } ;
struct dc {int dummy; } ;
struct common_irq_params {size_t irq_src; struct amdgpu_device* adev; } ;
struct TYPE_2__ {struct common_irq_params* pflip_params; struct common_irq_params* vupdate_params; struct common_irq_params* vblank_params; struct dc* dc; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  hpd_irq; TYPE_1__ dm; int /*<<< orphan*/  pageflip_irq; int /*<<< orphan*/  vupdate_irq; int /*<<< orphan*/  crtc_irq; } ;

/* Variables and functions */
 unsigned int AMDGPU_IRQ_CLIENTID_LEGACY ; 
 scalar_t__ CHIP_VEGA10 ; 
 size_t DC_IRQ_SOURCE_PFLIP_FIRST ; 
 size_t DC_IRQ_SOURCE_VBLANK1 ; 
 size_t DC_IRQ_SOURCE_VUPDATE1 ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 void* INTERRUPT_HIGH_IRQ_CONTEXT ; 
 void* INTERRUPT_POLARITY_DEFAULT ; 
 unsigned int SOC15_IH_CLIENTID_DCE ; 
 int VISLANDS30_IV_SRCID_D1_GRPH_PFLIP ; 
 int VISLANDS30_IV_SRCID_D1_VERTICAL_INTERRUPT0 ; 
 int VISLANDS30_IV_SRCID_D1_V_UPDATE_INT ; 
 int VISLANDS30_IV_SRCID_D6_GRPH_PFLIP ; 
 int VISLANDS30_IV_SRCID_D6_VERTICAL_INTERRUPT0 ; 
 int VISLANDS30_IV_SRCID_D6_V_UPDATE_INT ; 
 int VISLANDS30_IV_SRCID_HOTPLUG_DETECT_A ; 
 int /*<<< orphan*/  amdgpu_dm_irq_register_interrupt (struct amdgpu_device*,struct dc_interrupt_params*,int /*<<< orphan*/ ,struct common_irq_params*) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,unsigned int,int,int /*<<< orphan*/ *) ; 
 void* dc_interrupt_to_irq_source (struct dc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_crtc_high_irq ; 
 int /*<<< orphan*/  dm_pflip_high_irq ; 
 int /*<<< orphan*/  dm_vupdate_high_irq ; 
 int /*<<< orphan*/  register_hpd_handlers (struct amdgpu_device*) ; 

__attribute__((used)) static int dce110_register_irq_handlers(struct amdgpu_device *adev)
{
	struct dc *dc = adev->dm.dc;
	struct common_irq_params *c_irq_params;
	struct dc_interrupt_params int_params = {0};
	int r;
	int i;
	unsigned client_id = AMDGPU_IRQ_CLIENTID_LEGACY;

	if (adev->asic_type >= CHIP_VEGA10)
		client_id = SOC15_IH_CLIENTID_DCE;

	int_params.requested_polarity = INTERRUPT_POLARITY_DEFAULT;
	int_params.current_polarity = INTERRUPT_POLARITY_DEFAULT;

	/*
	 * Actions of amdgpu_irq_add_id():
	 * 1. Register a set() function with base driver.
	 *    Base driver will call set() function to enable/disable an
	 *    interrupt in DC hardware.
	 * 2. Register amdgpu_dm_irq_handler().
	 *    Base driver will call amdgpu_dm_irq_handler() for ALL interrupts
	 *    coming from DC hardware.
	 *    amdgpu_dm_irq_handler() will re-direct the interrupt to DC
	 *    for acknowledging and handling. */

	/* Use VBLANK interrupt */
	for (i = VISLANDS30_IV_SRCID_D1_VERTICAL_INTERRUPT0; i <= VISLANDS30_IV_SRCID_D6_VERTICAL_INTERRUPT0; i++) {
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->crtc_irq);
		if (r) {
			DRM_ERROR("Failed to add crtc irq id!\n");
			return r;
		}

		int_params.int_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		int_params.irq_source =
			dc_interrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.vblank_params[int_params.irq_source - DC_IRQ_SOURCE_VBLANK1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = int_params.irq_source;

		amdgpu_dm_irq_register_interrupt(adev, &int_params,
				dm_crtc_high_irq, c_irq_params);
	}

	/* Use VUPDATE interrupt */
	for (i = VISLANDS30_IV_SRCID_D1_V_UPDATE_INT; i <= VISLANDS30_IV_SRCID_D6_V_UPDATE_INT; i += 2) {
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->vupdate_irq);
		if (r) {
			DRM_ERROR("Failed to add vupdate irq id!\n");
			return r;
		}

		int_params.int_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		int_params.irq_source =
			dc_interrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.vupdate_params[int_params.irq_source - DC_IRQ_SOURCE_VUPDATE1];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = int_params.irq_source;

		amdgpu_dm_irq_register_interrupt(adev, &int_params,
				dm_vupdate_high_irq, c_irq_params);
	}

	/* Use GRPH_PFLIP interrupt */
	for (i = VISLANDS30_IV_SRCID_D1_GRPH_PFLIP;
			i <= VISLANDS30_IV_SRCID_D6_GRPH_PFLIP; i += 2) {
		r = amdgpu_irq_add_id(adev, client_id, i, &adev->pageflip_irq);
		if (r) {
			DRM_ERROR("Failed to add page flip irq id!\n");
			return r;
		}

		int_params.int_context = INTERRUPT_HIGH_IRQ_CONTEXT;
		int_params.irq_source =
			dc_interrupt_to_irq_source(dc, i, 0);

		c_irq_params = &adev->dm.pflip_params[int_params.irq_source - DC_IRQ_SOURCE_PFLIP_FIRST];

		c_irq_params->adev = adev;
		c_irq_params->irq_src = int_params.irq_source;

		amdgpu_dm_irq_register_interrupt(adev, &int_params,
				dm_pflip_high_irq, c_irq_params);

	}

	/* HPD */
	r = amdgpu_irq_add_id(adev, client_id,
			VISLANDS30_IV_SRCID_HOTPLUG_DETECT_A, &adev->hpd_irq);
	if (r) {
		DRM_ERROR("Failed to add hpd irq id!\n");
		return r;
	}

	register_hpd_handlers(adev);

	return 0;
}