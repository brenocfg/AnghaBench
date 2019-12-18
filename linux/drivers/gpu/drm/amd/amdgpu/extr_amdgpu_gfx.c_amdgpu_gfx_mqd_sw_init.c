#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int name; int /*<<< orphan*/  mqd_ptr; int /*<<< orphan*/  mqd_gpu_addr; int /*<<< orphan*/  mqd_obj; } ;
struct TYPE_7__ {void** mqd_backup; } ;
struct TYPE_6__ {void** mqd_backup; } ;
struct TYPE_5__ {struct amdgpu_ring ring; } ;
struct TYPE_8__ {int num_gfx_rings; int num_compute_rings; TYPE_3__ mec; struct amdgpu_ring* compute_ring; TYPE_2__ me; struct amdgpu_ring* gfx_ring; TYPE_1__ kiq; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  dev; TYPE_4__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 size_t AMDGPU_MAX_COMPUTE_RINGS ; 
 scalar_t__ CHIP_NAVI10 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ amdgpu_async_gfx_ring ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

int amdgpu_gfx_mqd_sw_init(struct amdgpu_device *adev,
			   unsigned mqd_size)
{
	struct amdgpu_ring *ring = NULL;
	int r, i;

	/* create MQD for KIQ */
	ring = &adev->gfx.kiq.ring;
	if (!ring->mqd_obj) {
		/* originaly the KIQ MQD is put in GTT domain, but for SRIOV VRAM domain is a must
		 * otherwise hypervisor trigger SAVE_VF fail after driver unloaded which mean MQD
		 * deallocated and gart_unbind, to strict diverage we decide to use VRAM domain for
		 * KIQ MQD no matter SRIOV or Bare-metal
		 */
		r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_VRAM, &ring->mqd_obj,
					    &ring->mqd_gpu_addr, &ring->mqd_ptr);
		if (r) {
			dev_warn(adev->dev, "failed to create ring mqd ob (%d)", r);
			return r;
		}

		/* prepare MQD backup */
		adev->gfx.mec.mqd_backup[AMDGPU_MAX_COMPUTE_RINGS] = kmalloc(mqd_size, GFP_KERNEL);
		if (!adev->gfx.mec.mqd_backup[AMDGPU_MAX_COMPUTE_RINGS])
				dev_warn(adev->dev, "no memory to create MQD backup for ring %s\n", ring->name);
	}

	if (adev->asic_type >= CHIP_NAVI10 && amdgpu_async_gfx_ring) {
		/* create MQD for each KGQ */
		for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
			ring = &adev->gfx.gfx_ring[i];
			if (!ring->mqd_obj) {
				r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
							    AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
							    &ring->mqd_gpu_addr, &ring->mqd_ptr);
				if (r) {
					dev_warn(adev->dev, "failed to create ring mqd bo (%d)", r);
					return r;
				}

				/* prepare MQD backup */
				adev->gfx.me.mqd_backup[i] = kmalloc(mqd_size, GFP_KERNEL);
				if (!adev->gfx.me.mqd_backup[i])
					dev_warn(adev->dev, "no memory to create MQD backup for ring %s\n", ring->name);
			}
		}
	}

	/* create MQD for each KCQ */
	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		ring = &adev->gfx.compute_ring[i];
		if (!ring->mqd_obj) {
			r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
						    AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
						    &ring->mqd_gpu_addr, &ring->mqd_ptr);
			if (r) {
				dev_warn(adev->dev, "failed to create ring mqd bo (%d)", r);
				return r;
			}

			/* prepare MQD backup */
			adev->gfx.mec.mqd_backup[i] = kmalloc(mqd_size, GFP_KERNEL);
			if (!adev->gfx.mec.mqd_backup[i])
				dev_warn(adev->dev, "no memory to create MQD backup for ring %s\n", ring->name);
		}
	}

	return 0;
}