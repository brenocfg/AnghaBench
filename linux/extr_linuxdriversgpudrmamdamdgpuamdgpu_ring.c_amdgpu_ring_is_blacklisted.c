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
struct amdgpu_ring {int idx; } ;

/* Variables and functions */

__attribute__((used)) static bool amdgpu_ring_is_blacklisted(struct amdgpu_ring *ring,
				       int *blacklist, int num_blacklist)
{
	int i;

	for (i = 0; i < num_blacklist; i++) {
		if (ring->idx == blacklist[i])
			return true;
	}

	return false;
}