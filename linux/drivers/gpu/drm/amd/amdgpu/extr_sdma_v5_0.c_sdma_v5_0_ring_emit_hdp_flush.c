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
typedef  int u32 ;
struct nbio_hdp_flush_reg {int ref_and_mask_sdma0; int ref_and_mask_sdma1; } ;
struct amdgpu_ring {scalar_t__ me; struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int (* get_hdp_flush_done_offset ) (struct amdgpu_device*) ;int (* get_hdp_flush_req_offset ) (struct amdgpu_device*) ;struct nbio_hdp_flush_reg* hdp_flush_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OP_POLL_REGMEM ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_INTERVAL (int) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_FUNC (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int stub1 (struct amdgpu_device*) ; 
 int stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static void sdma_v5_0_ring_emit_hdp_flush(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u32 ref_and_mask = 0;
	const struct nbio_hdp_flush_reg *nbio_hf_reg = adev->nbio_funcs->hdp_flush_reg;

	if (ring->me == 0)
		ref_and_mask = nbio_hf_reg->ref_and_mask_sdma0;
	else
		ref_and_mask = nbio_hf_reg->ref_and_mask_sdma1;

	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(1) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3)); /* == */
	amdgpu_ring_write(ring, (adev->nbio_funcs->get_hdp_flush_done_offset(adev)) << 2);
	amdgpu_ring_write(ring, (adev->nbio_funcs->get_hdp_flush_req_offset(adev)) << 2);
	amdgpu_ring_write(ring, ref_and_mask); /* reference */
	amdgpu_ring_write(ring, ref_and_mask); /* mask */
	amdgpu_ring_write(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10)); /* retry count, poll interval */
}