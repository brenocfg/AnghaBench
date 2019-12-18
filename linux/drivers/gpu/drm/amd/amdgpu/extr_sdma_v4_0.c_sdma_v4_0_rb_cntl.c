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
struct amdgpu_ring {int ring_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_SIZE ; 
 int /*<<< orphan*/  RB_SWAP_ENABLE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPTR_WRITEBACK_SWAP_ENABLE ; 
 int /*<<< orphan*/  SDMA0_GFX_RB_CNTL ; 
 int order_base_2 (int) ; 

__attribute__((used)) static uint32_t sdma_v4_0_rb_cntl(struct amdgpu_ring *ring, uint32_t rb_cntl)
{
	/* Set ring buffer size in dwords */
	uint32_t rb_bufsz = order_base_2(ring->ring_size / 4);

	rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SIZE, rb_bufsz);
#ifdef __BIG_ENDIAN
	rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SWAP_ENABLE, 1);
	rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL,
				RPTR_WRITEBACK_SWAP_ENABLE, 1);
#endif
	return rb_cntl;
}