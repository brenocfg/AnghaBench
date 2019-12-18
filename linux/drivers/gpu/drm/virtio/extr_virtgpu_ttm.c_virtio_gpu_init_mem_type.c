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
typedef  int uint32_t ;
struct ttm_mem_type_manager {void* default_caching; void* available_caching; void* flags; int /*<<< orphan*/ * func; } ;
struct ttm_bo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int EINVAL ; 
 void* TTM_MEMTYPE_FLAG_MAPPABLE ; 
 void* TTM_PL_FLAG_CACHED ; 
 void* TTM_PL_MASK_CACHING ; 
#define  TTM_PL_SYSTEM 129 
#define  TTM_PL_TT 128 
 int /*<<< orphan*/  virtio_gpu_bo_manager_func ; 

__attribute__((used)) static int virtio_gpu_init_mem_type(struct ttm_bo_device *bdev, uint32_t type,
				    struct ttm_mem_type_manager *man)
{
	switch (type) {
	case TTM_PL_SYSTEM:
		/* System memory */
		man->flags = TTM_MEMTYPE_FLAG_MAPPABLE;
		man->available_caching = TTM_PL_MASK_CACHING;
		man->default_caching = TTM_PL_FLAG_CACHED;
		break;
	case TTM_PL_TT:
		man->func = &virtio_gpu_bo_manager_func;
		man->flags = TTM_MEMTYPE_FLAG_MAPPABLE;
		man->available_caching = TTM_PL_MASK_CACHING;
		man->default_caching = TTM_PL_FLAG_CACHED;
		break;
	default:
		DRM_ERROR("Unsupported memory type %u\n", (unsigned int)type);
		return -EINVAL;
	}
	return 0;
}