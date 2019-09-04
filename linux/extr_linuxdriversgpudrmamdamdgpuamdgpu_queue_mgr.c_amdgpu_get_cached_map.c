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

__attribute__((used)) static struct amdgpu_ring *amdgpu_get_cached_map(struct amdgpu_queue_mapper *mapper,
					  int ring)
{
	return mapper->queue_map[ring];
}