#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_ring {int wptr; struct amdgpu_device* adev; } ;
struct TYPE_3__ {int /*<<< orphan*/  nop; } ;
struct TYPE_4__ {TYPE_1__ internal; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 

void vcn_v2_0_dec_ring_insert_nop(struct amdgpu_ring *ring, uint32_t count)
{
	struct amdgpu_device *adev = ring->adev;
	int i;

	WARN_ON(ring->wptr % 2 || count % 2);

	for (i = 0; i < count / 2; i++) {
		amdgpu_ring_write(ring, PACKET0(adev->vcn.internal.nop, 0));
		amdgpu_ring_write(ring, 0);
	}
}