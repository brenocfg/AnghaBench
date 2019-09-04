#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct kfd_process_device {int /*<<< orphan*/  scratch_base; int /*<<< orphan*/  scratch_limit; TYPE_3__* dev; int /*<<< orphan*/  gpuvm_base; scalar_t__ gpuvm_limit; int /*<<< orphan*/  lds_base; int /*<<< orphan*/  lds_limit; } ;
struct TYPE_5__ {scalar_t__ gpuvm_size; } ;
struct TYPE_6__ {TYPE_2__ shared_resources; TYPE_1__* device_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  needs_iommu_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_GPUVM_APP_BASE_VI (scalar_t__) ; 
 scalar_t__ MAKE_GPUVM_APP_LIMIT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MAKE_LDS_APP_BASE_VI () ; 
 int /*<<< orphan*/  MAKE_LDS_APP_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_SCRATCH_APP_BASE_VI () ; 
 int /*<<< orphan*/  MAKE_SCRATCH_APP_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVM_USER_BASE ; 

__attribute__((used)) static void kfd_init_apertures_vi(struct kfd_process_device *pdd, uint8_t id)
{
	/*
	 * node id couldn't be 0 - the three MSB bits of
	 * aperture shoudn't be 0
	 */
	pdd->lds_base = MAKE_LDS_APP_BASE_VI();
	pdd->lds_limit = MAKE_LDS_APP_LIMIT(pdd->lds_base);

	if (!pdd->dev->device_info->needs_iommu_device) {
		/* dGPUs: SVM aperture starting at 0
		 * with small reserved space for kernel.
		 * Set them to CANONICAL addresses.
		 */
		pdd->gpuvm_base = SVM_USER_BASE;
		pdd->gpuvm_limit =
			pdd->dev->shared_resources.gpuvm_size - 1;
	} else {
		/* set them to non CANONICAL addresses, and no SVM is
		 * allocated.
		 */
		pdd->gpuvm_base = MAKE_GPUVM_APP_BASE_VI(id + 1);
		pdd->gpuvm_limit = MAKE_GPUVM_APP_LIMIT(pdd->gpuvm_base,
				pdd->dev->shared_resources.gpuvm_size);
	}

	pdd->scratch_base = MAKE_SCRATCH_APP_BASE_VI();
	pdd->scratch_limit = MAKE_SCRATCH_APP_LIMIT(pdd->scratch_base);
}