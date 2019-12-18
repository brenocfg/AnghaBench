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
struct nbio_hdp_flush_reg {int ref_and_mask_sdma0; } ;
struct amdgpu_ring {int me; struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_hdp_flush_req_offset ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* get_hdp_flush_done_offset ) (struct amdgpu_device*) ;struct nbio_hdp_flush_reg* hdp_flush_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_v4_0_wait_reg_mem (struct amdgpu_ring*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static void sdma_v4_0_ring_emit_hdp_flush(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u32 ref_and_mask = 0;
	const struct nbio_hdp_flush_reg *nbio_hf_reg = adev->nbio_funcs->hdp_flush_reg;

	ref_and_mask = nbio_hf_reg->ref_and_mask_sdma0 << ring->me;

	sdma_v4_0_wait_reg_mem(ring, 0, 1,
			       adev->nbio_funcs->get_hdp_flush_done_offset(adev),
			       adev->nbio_funcs->get_hdp_flush_req_offset(adev),
			       ref_and_mask, ref_and_mask, 10);
}