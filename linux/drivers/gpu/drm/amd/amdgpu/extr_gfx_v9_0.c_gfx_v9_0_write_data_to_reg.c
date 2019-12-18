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
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_WRITE_DATA ; 
 int WRITE_DATA_DST_SEL (int /*<<< orphan*/ ) ; 
 int WRITE_DATA_ENGINE_SEL (int) ; 
 int WR_CONFIRM ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void gfx_v9_0_write_data_to_reg(struct amdgpu_ring *ring, int eng_sel,
				       bool wc, uint32_t reg, uint32_t val)
{
	amdgpu_ring_write(ring, PACKET3(PACKET3_WRITE_DATA, 3));
	amdgpu_ring_write(ring, WRITE_DATA_ENGINE_SEL(eng_sel) |
				WRITE_DATA_DST_SEL(0) |
				(wc ? WR_CONFIRM : 0));
	amdgpu_ring_write(ring, reg);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, val);
}