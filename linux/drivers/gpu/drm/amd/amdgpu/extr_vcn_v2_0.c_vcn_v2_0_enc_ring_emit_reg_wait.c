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
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int VCN_ENC_CMD_REG_WAIT ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

void vcn_v2_0_enc_ring_emit_reg_wait(struct amdgpu_ring *ring, uint32_t reg,
				uint32_t val, uint32_t mask)
{
	amdgpu_ring_write(ring, VCN_ENC_CMD_REG_WAIT);
	amdgpu_ring_write(ring, reg << 2);
	amdgpu_ring_write(ring, mask);
	amdgpu_ring_write(ring, val);
}