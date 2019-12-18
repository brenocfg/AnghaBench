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
typedef  int u32 ;
struct nbio_hdp_flush_reg {int ref_and_mask_cp2; int ref_and_mask_cp6; int ref_and_mask_cp0; } ;
struct amdgpu_ring {int me; int pipe; TYPE_1__* funcs; struct amdgpu_device* adev; } ;
struct amdgpu_device {TYPE_2__* nbio_funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_hdp_flush_done_offset ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* get_hdp_flush_req_offset ) (struct amdgpu_device*) ;struct nbio_hdp_flush_reg* hdp_flush_reg; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_COMPUTE ; 
 int /*<<< orphan*/  gfx_v9_0_wait_reg_mem (struct amdgpu_ring*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static void gfx_v9_0_ring_emit_hdp_flush(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u32 ref_and_mask, reg_mem_engine;
	const struct nbio_hdp_flush_reg *nbio_hf_reg = adev->nbio_funcs->hdp_flush_reg;

	if (ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE) {
		switch (ring->me) {
		case 1:
			ref_and_mask = nbio_hf_reg->ref_and_mask_cp2 << ring->pipe;
			break;
		case 2:
			ref_and_mask = nbio_hf_reg->ref_and_mask_cp6 << ring->pipe;
			break;
		default:
			return;
		}
		reg_mem_engine = 0;
	} else {
		ref_and_mask = nbio_hf_reg->ref_and_mask_cp0;
		reg_mem_engine = 1; /* pfp */
	}

	gfx_v9_0_wait_reg_mem(ring, reg_mem_engine, 0, 1,
			      adev->nbio_funcs->get_hdp_flush_req_offset(adev),
			      adev->nbio_funcs->get_hdp_flush_done_offset(adev),
			      ref_and_mask, ref_and_mask, 0x20);
}