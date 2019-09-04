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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_ring {int idx; } ;
struct amdgpu_queue_mapper {struct amdgpu_ring** queue_map; int /*<<< orphan*/  hw_ip; } ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  ring_blacklist ;

/* Variables and functions */
 int AMDGPU_MAX_RINGS ; 
 int amdgpu_hw_ip_to_ring_type (int /*<<< orphan*/ ) ; 
 int amdgpu_ring_lru_get (struct amdgpu_device*,int,int*,int,int,struct amdgpu_ring**) ; 
 int amdgpu_update_cached_map (struct amdgpu_queue_mapper*,int /*<<< orphan*/ ,struct amdgpu_ring*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int amdgpu_lru_map(struct amdgpu_device *adev,
			  struct amdgpu_queue_mapper *mapper,
			  u32 user_ring, bool lru_pipe_order,
			  struct amdgpu_ring **out_ring)
{
	int r, i, j;
	int ring_type = amdgpu_hw_ip_to_ring_type(mapper->hw_ip);
	int ring_blacklist[AMDGPU_MAX_RINGS];
	struct amdgpu_ring *ring;

	/* 0 is a valid ring index, so initialize to -1 */
	memset(ring_blacklist, 0xff, sizeof(ring_blacklist));

	for (i = 0, j = 0; i < AMDGPU_MAX_RINGS; i++) {
		ring = mapper->queue_map[i];
		if (ring)
			ring_blacklist[j++] = ring->idx;
	}

	r = amdgpu_ring_lru_get(adev, ring_type, ring_blacklist,
				j, lru_pipe_order, out_ring);
	if (r)
		return r;

	return amdgpu_update_cached_map(mapper, user_ring, *out_ring);
}