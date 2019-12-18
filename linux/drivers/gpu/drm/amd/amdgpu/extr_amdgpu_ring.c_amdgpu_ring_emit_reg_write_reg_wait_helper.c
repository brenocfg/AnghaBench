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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ring_emit_reg_wait (struct amdgpu_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_wreg (struct amdgpu_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void amdgpu_ring_emit_reg_write_reg_wait_helper(struct amdgpu_ring *ring,
						uint32_t reg0, uint32_t reg1,
						uint32_t ref, uint32_t mask)
{
	amdgpu_ring_emit_wreg(ring, reg0, ref);
	amdgpu_ring_emit_reg_wait(ring, reg1, mask, mask);
}