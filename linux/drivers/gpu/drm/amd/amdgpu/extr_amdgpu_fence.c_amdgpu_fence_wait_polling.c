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
typedef  scalar_t__ uint32_t ;
struct amdgpu_ring {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ amdgpu_fence_read (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  udelay (int) ; 

signed long amdgpu_fence_wait_polling(struct amdgpu_ring *ring,
				      uint32_t wait_seq,
				      signed long timeout)
{
	uint32_t seq;

	do {
		seq = amdgpu_fence_read(ring);
		udelay(5);
		timeout -= 5;
	} while ((int32_t)(wait_seq - seq) > 0 && timeout > 0);

	return timeout > 0 ? timeout : 0;
}