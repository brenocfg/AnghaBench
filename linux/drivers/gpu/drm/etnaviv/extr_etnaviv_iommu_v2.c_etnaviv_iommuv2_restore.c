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
struct etnaviv_iommu_context {int dummy; } ;
struct etnaviv_gpu {int sec_mode; } ;

/* Variables and functions */
#define  ETNA_SEC_KERNEL 129 
#define  ETNA_SEC_NONE 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  etnaviv_iommuv2_restore_nonsec (struct etnaviv_gpu*,struct etnaviv_iommu_context*) ; 
 int /*<<< orphan*/  etnaviv_iommuv2_restore_sec (struct etnaviv_gpu*,struct etnaviv_iommu_context*) ; 

__attribute__((used)) static void etnaviv_iommuv2_restore(struct etnaviv_gpu *gpu,
				    struct etnaviv_iommu_context *context)
{
	switch (gpu->sec_mode) {
	case ETNA_SEC_NONE:
		etnaviv_iommuv2_restore_nonsec(gpu, context);
		break;
	case ETNA_SEC_KERNEL:
		etnaviv_iommuv2_restore_sec(gpu, context);
		break;
	default:
		WARN(1, "unhandled GPU security mode\n");
		break;
	}
}