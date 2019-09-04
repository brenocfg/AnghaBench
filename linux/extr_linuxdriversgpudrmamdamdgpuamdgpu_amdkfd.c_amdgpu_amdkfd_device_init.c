#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct kgd2kfd_shared_resources {int num_pipe_per_mec; int num_queue_per_pipe; int reserved_doorbell_mask; int reserved_doorbell_val; void*** sdma_doorbell; int /*<<< orphan*/  doorbell_start_offset; int /*<<< orphan*/  doorbell_aperture_size; int /*<<< orphan*/  doorbell_physical_address; int /*<<< orphan*/  queue_bitmap; int /*<<< orphan*/  drm_render_minor; int /*<<< orphan*/  gpuvm_size; int /*<<< orphan*/  compute_vmid_bitmap; } ;
struct TYPE_14__ {int num_pipe_per_mec; int num_queue_per_pipe; int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_12__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; scalar_t__ me; scalar_t__ ready; } ;
struct TYPE_13__ {TYPE_4__ ring; } ;
struct TYPE_15__ {TYPE_6__ mec; TYPE_5__ kiq; } ;
struct TYPE_9__ {int max_pfn; } ;
struct amdgpu_device {scalar_t__ asic_type; scalar_t__ kfd; TYPE_7__ gfx; TYPE_3__* ddev; TYPE_1__ vm_manager; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* device_init ) (scalar_t__,struct kgd2kfd_shared_resources*) ;} ;
struct TYPE_11__ {TYPE_2__* render; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 void* AMDGPU_DOORBELL64_sDMA_ENGINE0 ; 
 void* AMDGPU_DOORBELL64_sDMA_ENGINE1 ; 
 int AMDGPU_GPU_PAGE_SHIFT ; 
 int /*<<< orphan*/  AMDGPU_VA_HOLE_START ; 
 scalar_t__ CHIP_VEGA10 ; 
 int KGD_MAX_QUEUES ; 
 int /*<<< orphan*/  amdgpu_doorbell_get_kfd_info (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_gfx_queue_to_bit (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_complement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_vmid_bitmap ; 
 TYPE_8__* kgd2kfd ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,struct kgd2kfd_shared_resources*) ; 

void amdgpu_amdkfd_device_init(struct amdgpu_device *adev)
{
	int i;
	int last_valid_bit;
	if (adev->kfd) {
		struct kgd2kfd_shared_resources gpu_resources = {
			.compute_vmid_bitmap = compute_vmid_bitmap,
			.num_pipe_per_mec = adev->gfx.mec.num_pipe_per_mec,
			.num_queue_per_pipe = adev->gfx.mec.num_queue_per_pipe,
			.gpuvm_size = min(adev->vm_manager.max_pfn
					  << AMDGPU_GPU_PAGE_SHIFT,
					  AMDGPU_VA_HOLE_START),
			.drm_render_minor = adev->ddev->render->index
		};

		/* this is going to have a few of the MSBs set that we need to
		 * clear */
		bitmap_complement(gpu_resources.queue_bitmap,
				  adev->gfx.mec.queue_bitmap,
				  KGD_MAX_QUEUES);

		/* remove the KIQ bit as well */
		if (adev->gfx.kiq.ring.ready)
			clear_bit(amdgpu_gfx_queue_to_bit(adev,
							  adev->gfx.kiq.ring.me - 1,
							  adev->gfx.kiq.ring.pipe,
							  adev->gfx.kiq.ring.queue),
				  gpu_resources.queue_bitmap);

		/* According to linux/bitmap.h we shouldn't use bitmap_clear if
		 * nbits is not compile time constant */
		last_valid_bit = 1 /* only first MEC can have compute queues */
				* adev->gfx.mec.num_pipe_per_mec
				* adev->gfx.mec.num_queue_per_pipe;
		for (i = last_valid_bit; i < KGD_MAX_QUEUES; ++i)
			clear_bit(i, gpu_resources.queue_bitmap);

		amdgpu_doorbell_get_kfd_info(adev,
				&gpu_resources.doorbell_physical_address,
				&gpu_resources.doorbell_aperture_size,
				&gpu_resources.doorbell_start_offset);
		if (adev->asic_type >= CHIP_VEGA10) {
			/* On SOC15 the BIF is involved in routing
			 * doorbells using the low 12 bits of the
			 * address. Communicate the assignments to
			 * KFD. KFD uses two doorbell pages per
			 * process in case of 64-bit doorbells so we
			 * can use each doorbell assignment twice.
			 */
			gpu_resources.sdma_doorbell[0][0] =
				AMDGPU_DOORBELL64_sDMA_ENGINE0;
			gpu_resources.sdma_doorbell[0][1] =
				AMDGPU_DOORBELL64_sDMA_ENGINE0 + 0x200;
			gpu_resources.sdma_doorbell[1][0] =
				AMDGPU_DOORBELL64_sDMA_ENGINE1;
			gpu_resources.sdma_doorbell[1][1] =
				AMDGPU_DOORBELL64_sDMA_ENGINE1 + 0x200;
			/* Doorbells 0x0f0-0ff and 0x2f0-2ff are reserved for
			 * SDMA, IH and VCN. So don't use them for the CP.
			 */
			gpu_resources.reserved_doorbell_mask = 0x1f0;
			gpu_resources.reserved_doorbell_val  = 0x0f0;
		}

		kgd2kfd->device_init(adev->kfd, &gpu_resources);
	}
}