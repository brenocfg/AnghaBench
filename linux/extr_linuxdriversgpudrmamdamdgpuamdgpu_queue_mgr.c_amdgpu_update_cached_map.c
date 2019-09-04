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
struct amdgpu_ring {int dummy; } ;
struct amdgpu_queue_mapper {struct amdgpu_ring** queue_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (struct amdgpu_ring*) ; 

__attribute__((used)) static int amdgpu_update_cached_map(struct amdgpu_queue_mapper *mapper,
			     int ring, struct amdgpu_ring *pring)
{
	if (WARN_ON(mapper->queue_map[ring])) {
		DRM_ERROR("Un-expected ring re-map\n");
		return -EINVAL;
	}

	mapper->queue_map[ring] = pring;

	return 0;
}