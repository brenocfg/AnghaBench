#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int /*<<< orphan*/  name; int /*<<< orphan*/ * funcs; } ;
struct TYPE_6__ {int num_enc_rings; TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_7__ {int num_types; } ;
struct TYPE_5__ {TYPE_3__ irq; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_CLIENTID_LEGACY ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ VISLANDS30_IV_SRCID_UVD_ENC_GEN_PURP ; 
 scalar_t__ VISLANDS30_IV_SRCID_UVD_SYSTEM_MESSAGE ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int amdgpu_uvd_entity_init (struct amdgpu_device*) ; 
 int amdgpu_uvd_resume (struct amdgpu_device*) ; 
 int amdgpu_uvd_sw_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ uvd_v6_0_enc_support (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v6_0_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	int i, r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* UVD TRAP */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_UVD_SYSTEM_MESSAGE, &adev->uvd.inst->irq);
	if (r)
		return r;

	/* UVD ENC TRAP */
	if (uvd_v6_0_enc_support(adev)) {
		for (i = 0; i < adev->uvd.num_enc_rings; ++i) {
			r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, i + VISLANDS30_IV_SRCID_UVD_ENC_GEN_PURP, &adev->uvd.inst->irq);
			if (r)
				return r;
		}
	}

	r = amdgpu_uvd_sw_init(adev);
	if (r)
		return r;

	if (!uvd_v6_0_enc_support(adev)) {
		for (i = 0; i < adev->uvd.num_enc_rings; ++i)
			adev->uvd.inst->ring_enc[i].funcs = NULL;

		adev->uvd.inst->irq.num_types = 1;
		adev->uvd.num_enc_rings = 0;

		DRM_INFO("UVD ENC is disabled\n");
	}

	ring = &adev->uvd.inst->ring;
	sprintf(ring->name, "uvd");
	r = amdgpu_ring_init(adev, ring, 512, &adev->uvd.inst->irq, 0);
	if (r)
		return r;

	r = amdgpu_uvd_resume(adev);
	if (r)
		return r;

	if (uvd_v6_0_enc_support(adev)) {
		for (i = 0; i < adev->uvd.num_enc_rings; ++i) {
			ring = &adev->uvd.inst->ring_enc[i];
			sprintf(ring->name, "uvd_enc%d", i);
			r = amdgpu_ring_init(adev, ring, 512, &adev->uvd.inst->irq, 0);
			if (r)
				return r;
		}
	}

	r = amdgpu_uvd_entity_init(adev);

	return r;
}