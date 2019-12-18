#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  sync_seq; int /*<<< orphan*/  last_seq; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_fence_process (struct amdgpu_ring*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int lower_32_bits (int) ; 

unsigned amdgpu_fence_count_emitted(struct amdgpu_ring *ring)
{
	uint64_t emitted;

	/* We are not protected by ring lock when reading the last sequence
	 * but it's ok to report slightly wrong fence count here.
	 */
	amdgpu_fence_process(ring);
	emitted = 0x100000000ull;
	emitted -= atomic_read(&ring->fence_drv.last_seq);
	emitted += READ_ONCE(ring->fence_drv.sync_seq);
	return lower_32_bits(emitted);
}