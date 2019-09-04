#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct radeon_ring {int me; int pipe; } ;
struct TYPE_14__ {int rptr; int ptr_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ring; int /*<<< orphan*/  enabled; } ;
struct TYPE_11__ {int high_to_low; int /*<<< orphan*/  work; } ;
struct TYPE_12__ {TYPE_4__ thermal; } ;
struct TYPE_13__ {int vblank_sync; TYPE_5__ dpm; } ;
struct TYPE_8__ {int disp_int; int disp_int_cont; int disp_int_cont2; int disp_int_cont3; int disp_int_cont4; int disp_int_cont5; } ;
struct TYPE_9__ {TYPE_1__ cik; } ;
struct TYPE_10__ {TYPE_2__ stat_regs; int /*<<< orphan*/ * pflip; int /*<<< orphan*/  vblank_queue; int /*<<< orphan*/ * crtc_vblank_int; } ;
struct radeon_device {int needs_reset; TYPE_7__ ih; TYPE_6__ pm; int /*<<< orphan*/  fence_queue; int /*<<< orphan*/  hotplug_work; int /*<<< orphan*/  dp_work; int /*<<< orphan*/  dev; TYPE_3__ irq; int /*<<< orphan*/  ddev; scalar_t__ shutdown; struct radeon_ring* ring; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int DC_HPD1_INTERRUPT ; 
 int DC_HPD1_RX_INTERRUPT ; 
 int DC_HPD2_INTERRUPT ; 
 int DC_HPD2_RX_INTERRUPT ; 
 int DC_HPD3_INTERRUPT ; 
 int DC_HPD3_RX_INTERRUPT ; 
 int DC_HPD4_INTERRUPT ; 
 int DC_HPD4_RX_INTERRUPT ; 
 int DC_HPD5_INTERRUPT ; 
 int DC_HPD5_RX_INTERRUPT ; 
 int DC_HPD6_INTERRUPT ; 
 int DC_HPD6_RX_INTERRUPT ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  IH_RB_RPTR ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int LB_D1_VBLANK_INTERRUPT ; 
 int LB_D1_VLINE_INTERRUPT ; 
 int LB_D2_VBLANK_INTERRUPT ; 
 int LB_D2_VLINE_INTERRUPT ; 
 int LB_D3_VBLANK_INTERRUPT ; 
 int LB_D3_VLINE_INTERRUPT ; 
 int LB_D4_VBLANK_INTERRUPT ; 
 int LB_D4_VLINE_INTERRUPT ; 
 int LB_D5_VBLANK_INTERRUPT ; 
 int LB_D5_VLINE_INTERRUPT ; 
 int LB_D6_VBLANK_INTERRUPT ; 
 int LB_D6_VLINE_INTERRUPT ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 size_t R600_RING_TYPE_UVD_INDEX ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRBM_INT_ACK ; 
 int /*<<< orphan*/  SRBM_READ_ERROR ; 
 size_t TN_RING_TYPE_VCE1_INDEX ; 
 size_t TN_RING_TYPE_VCE2_INDEX ; 
 int /*<<< orphan*/  VM_CONTEXT1_CNTL2 ; 
 int /*<<< orphan*/  VM_CONTEXT1_PROTECTION_FAULT_ADDR ; 
 int /*<<< orphan*/  VM_CONTEXT1_PROTECTION_FAULT_MCCLIENT ; 
 int /*<<< orphan*/  VM_CONTEXT1_PROTECTION_FAULT_STATUS ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int cik_get_ih_wptr (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_irq_ack (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_vm_decode_fault (struct radeon_device*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  drm_handle_vblank (int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_crtc_handle_flip (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_crtc_handle_vblank (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_fence_process (struct radeon_device*,size_t) ; 
 int /*<<< orphan*/  radeon_use_pflipirq ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

int cik_irq_process(struct radeon_device *rdev)
{
	struct radeon_ring *cp1_ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	struct radeon_ring *cp2_ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	u32 wptr;
	u32 rptr;
	u32 src_id, src_data, ring_id;
	u8 me_id, pipe_id, queue_id;
	u32 ring_index;
	bool queue_hotplug = false;
	bool queue_dp = false;
	bool queue_reset = false;
	u32 addr, status, mc_client;
	bool queue_thermal = false;

	if (!rdev->ih.enabled || rdev->shutdown)
		return IRQ_NONE;

	wptr = cik_get_ih_wptr(rdev);

restart_ih:
	/* is somebody else already processing irqs? */
	if (atomic_xchg(&rdev->ih.lock, 1))
		return IRQ_NONE;

	rptr = rdev->ih.rptr;
	DRM_DEBUG("cik_irq_process start: rptr %d, wptr %d\n", rptr, wptr);

	/* Order reading of wptr vs. reading of IH ring data */
	rmb();

	/* display interrupts */
	cik_irq_ack(rdev);

	while (rptr != wptr) {
		/* wptr/rptr are in bytes! */
		ring_index = rptr / 4;

		src_id =  le32_to_cpu(rdev->ih.ring[ring_index]) & 0xff;
		src_data = le32_to_cpu(rdev->ih.ring[ring_index + 1]) & 0xfffffff;
		ring_id = le32_to_cpu(rdev->ih.ring[ring_index + 2]) & 0xff;

		switch (src_id) {
		case 1: /* D1 vblank/vline */
			switch (src_data) {
			case 0: /* D1 vblank */
				if (!(rdev->irq.stat_regs.cik.disp_int & LB_D1_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				if (rdev->irq.crtc_vblank_int[0]) {
					drm_handle_vblank(rdev->ddev, 0);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				}
				if (atomic_read(&rdev->irq.pflip[0]))
					radeon_crtc_handle_vblank(rdev, 0);
				rdev->irq.stat_regs.cik.disp_int &= ~LB_D1_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D1 vblank\n");

				break;
			case 1: /* D1 vline */
				if (!(rdev->irq.stat_regs.cik.disp_int & LB_D1_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int &= ~LB_D1_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D1 vline\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 2: /* D2 vblank/vline */
			switch (src_data) {
			case 0: /* D2 vblank */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont & LB_D2_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				if (rdev->irq.crtc_vblank_int[1]) {
					drm_handle_vblank(rdev->ddev, 1);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				}
				if (atomic_read(&rdev->irq.pflip[1]))
					radeon_crtc_handle_vblank(rdev, 1);
				rdev->irq.stat_regs.cik.disp_int_cont &= ~LB_D2_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D2 vblank\n");

				break;
			case 1: /* D2 vline */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont & LB_D2_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont &= ~LB_D2_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D2 vline\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 3: /* D3 vblank/vline */
			switch (src_data) {
			case 0: /* D3 vblank */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont2 & LB_D3_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				if (rdev->irq.crtc_vblank_int[2]) {
					drm_handle_vblank(rdev->ddev, 2);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				}
				if (atomic_read(&rdev->irq.pflip[2]))
					radeon_crtc_handle_vblank(rdev, 2);
				rdev->irq.stat_regs.cik.disp_int_cont2 &= ~LB_D3_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D3 vblank\n");

				break;
			case 1: /* D3 vline */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont2 & LB_D3_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont2 &= ~LB_D3_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D3 vline\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 4: /* D4 vblank/vline */
			switch (src_data) {
			case 0: /* D4 vblank */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont3 & LB_D4_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				if (rdev->irq.crtc_vblank_int[3]) {
					drm_handle_vblank(rdev->ddev, 3);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				}
				if (atomic_read(&rdev->irq.pflip[3]))
					radeon_crtc_handle_vblank(rdev, 3);
				rdev->irq.stat_regs.cik.disp_int_cont3 &= ~LB_D4_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D4 vblank\n");

				break;
			case 1: /* D4 vline */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont3 & LB_D4_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont3 &= ~LB_D4_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D4 vline\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 5: /* D5 vblank/vline */
			switch (src_data) {
			case 0: /* D5 vblank */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont4 & LB_D5_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				if (rdev->irq.crtc_vblank_int[4]) {
					drm_handle_vblank(rdev->ddev, 4);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				}
				if (atomic_read(&rdev->irq.pflip[4]))
					radeon_crtc_handle_vblank(rdev, 4);
				rdev->irq.stat_regs.cik.disp_int_cont4 &= ~LB_D5_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D5 vblank\n");

				break;
			case 1: /* D5 vline */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont4 & LB_D5_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont4 &= ~LB_D5_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D5 vline\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 6: /* D6 vblank/vline */
			switch (src_data) {
			case 0: /* D6 vblank */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont5 & LB_D6_VBLANK_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				if (rdev->irq.crtc_vblank_int[5]) {
					drm_handle_vblank(rdev->ddev, 5);
					rdev->pm.vblank_sync = true;
					wake_up(&rdev->irq.vblank_queue);
				}
				if (atomic_read(&rdev->irq.pflip[5]))
					radeon_crtc_handle_vblank(rdev, 5);
				rdev->irq.stat_regs.cik.disp_int_cont5 &= ~LB_D6_VBLANK_INTERRUPT;
				DRM_DEBUG("IH: D6 vblank\n");

				break;
			case 1: /* D6 vline */
				if (!(rdev->irq.stat_regs.cik.disp_int_cont5 & LB_D6_VLINE_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont5 &= ~LB_D6_VLINE_INTERRUPT;
				DRM_DEBUG("IH: D6 vline\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 8: /* D1 page flip */
		case 10: /* D2 page flip */
		case 12: /* D3 page flip */
		case 14: /* D4 page flip */
		case 16: /* D5 page flip */
		case 18: /* D6 page flip */
			DRM_DEBUG("IH: D%d flip\n", ((src_id - 8) >> 1) + 1);
			if (radeon_use_pflipirq > 0)
				radeon_crtc_handle_flip(rdev, (src_id - 8) >> 1);
			break;
		case 42: /* HPD hotplug */
			switch (src_data) {
			case 0:
				if (!(rdev->irq.stat_regs.cik.disp_int & DC_HPD1_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int &= ~DC_HPD1_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD1\n");

				break;
			case 1:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont & DC_HPD2_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont &= ~DC_HPD2_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD2\n");

				break;
			case 2:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont2 & DC_HPD3_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont2 &= ~DC_HPD3_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD3\n");

				break;
			case 3:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont3 & DC_HPD4_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont3 &= ~DC_HPD4_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD4\n");

				break;
			case 4:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont4 & DC_HPD5_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont4 &= ~DC_HPD5_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD5\n");

				break;
			case 5:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont5 & DC_HPD6_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont5 &= ~DC_HPD6_INTERRUPT;
				queue_hotplug = true;
				DRM_DEBUG("IH: HPD6\n");

				break;
			case 6:
				if (!(rdev->irq.stat_regs.cik.disp_int & DC_HPD1_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int &= ~DC_HPD1_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 1\n");

				break;
			case 7:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont & DC_HPD2_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont &= ~DC_HPD2_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 2\n");

				break;
			case 8:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont2 & DC_HPD3_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont2 &= ~DC_HPD3_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 3\n");

				break;
			case 9:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont3 & DC_HPD4_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont3 &= ~DC_HPD4_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 4\n");

				break;
			case 10:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont4 & DC_HPD5_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont4 &= ~DC_HPD5_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 5\n");

				break;
			case 11:
				if (!(rdev->irq.stat_regs.cik.disp_int_cont5 & DC_HPD6_RX_INTERRUPT))
					DRM_DEBUG("IH: IH event w/o asserted irq bit?\n");

				rdev->irq.stat_regs.cik.disp_int_cont5 &= ~DC_HPD6_RX_INTERRUPT;
				queue_dp = true;
				DRM_DEBUG("IH: HPD_RX 6\n");

				break;
			default:
				DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 96:
			DRM_ERROR("SRBM_READ_ERROR: 0x%x\n", RREG32(SRBM_READ_ERROR));
			WREG32(SRBM_INT_ACK, 0x1);
			break;
		case 124: /* UVD */
			DRM_DEBUG("IH: UVD int: 0x%08x\n", src_data);
			radeon_fence_process(rdev, R600_RING_TYPE_UVD_INDEX);
			break;
		case 146:
		case 147:
			addr = RREG32(VM_CONTEXT1_PROTECTION_FAULT_ADDR);
			status = RREG32(VM_CONTEXT1_PROTECTION_FAULT_STATUS);
			mc_client = RREG32(VM_CONTEXT1_PROTECTION_FAULT_MCCLIENT);
			/* reset addr and status */
			WREG32_P(VM_CONTEXT1_CNTL2, 1, ~1);
			if (addr == 0x0 && status == 0x0)
				break;
			dev_err(rdev->dev, "GPU fault detected: %d 0x%08x\n", src_id, src_data);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
				addr);
			dev_err(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
				status);
			cik_vm_decode_fault(rdev, status, addr, mc_client);
			break;
		case 167: /* VCE */
			DRM_DEBUG("IH: VCE int: 0x%08x\n", src_data);
			switch (src_data) {
			case 0:
				radeon_fence_process(rdev, TN_RING_TYPE_VCE1_INDEX);
				break;
			case 1:
				radeon_fence_process(rdev, TN_RING_TYPE_VCE2_INDEX);
				break;
			default:
				DRM_ERROR("Unhandled interrupt: %d %d\n", src_id, src_data);
				break;
			}
			break;
		case 176: /* GFX RB CP_INT */
		case 177: /* GFX IB CP_INT */
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
			break;
		case 181: /* CP EOP event */
			DRM_DEBUG("IH: CP EOP\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x60) >> 5;
			pipe_id = (ring_id & 0x18) >> 3;
			queue_id = (ring_id & 0x7) >> 0;
			switch (me_id) {
			case 0:
				radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
				break;
			case 1:
			case 2:
				if ((cp1_ring->me == me_id) & (cp1_ring->pipe == pipe_id))
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
				if ((cp2_ring->me == me_id) & (cp2_ring->pipe == pipe_id))
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
				break;
			}
			break;
		case 184: /* CP Privileged reg access */
			DRM_ERROR("Illegal register access in command stream\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x60) >> 5;
			pipe_id = (ring_id & 0x18) >> 3;
			queue_id = (ring_id & 0x7) >> 0;
			switch (me_id) {
			case 0:
				/* This results in a full GPU reset, but all we need to do is soft
				 * reset the CP for gfx
				 */
				queue_reset = true;
				break;
			case 1:
				/* XXX compute */
				queue_reset = true;
				break;
			case 2:
				/* XXX compute */
				queue_reset = true;
				break;
			}
			break;
		case 185: /* CP Privileged inst */
			DRM_ERROR("Illegal instruction in command stream\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x60) >> 5;
			pipe_id = (ring_id & 0x18) >> 3;
			queue_id = (ring_id & 0x7) >> 0;
			switch (me_id) {
			case 0:
				/* This results in a full GPU reset, but all we need to do is soft
				 * reset the CP for gfx
				 */
				queue_reset = true;
				break;
			case 1:
				/* XXX compute */
				queue_reset = true;
				break;
			case 2:
				/* XXX compute */
				queue_reset = true;
				break;
			}
			break;
		case 224: /* SDMA trap event */
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x3) >> 0;
			queue_id = (ring_id & 0xc) >> 2;
			DRM_DEBUG("IH: SDMA trap\n");
			switch (me_id) {
			case 0:
				switch (queue_id) {
				case 0:
					radeon_fence_process(rdev, R600_RING_TYPE_DMA_INDEX);
					break;
				case 1:
					/* XXX compute */
					break;
				case 2:
					/* XXX compute */
					break;
				}
				break;
			case 1:
				switch (queue_id) {
				case 0:
					radeon_fence_process(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
					break;
				case 1:
					/* XXX compute */
					break;
				case 2:
					/* XXX compute */
					break;
				}
				break;
			}
			break;
		case 230: /* thermal low to high */
			DRM_DEBUG("IH: thermal low to high\n");
			rdev->pm.dpm.thermal.high_to_low = false;
			queue_thermal = true;
			break;
		case 231: /* thermal high to low */
			DRM_DEBUG("IH: thermal high to low\n");
			rdev->pm.dpm.thermal.high_to_low = true;
			queue_thermal = true;
			break;
		case 233: /* GUI IDLE */
			DRM_DEBUG("IH: GUI idle\n");
			break;
		case 241: /* SDMA Privileged inst */
		case 247: /* SDMA Privileged inst */
			DRM_ERROR("Illegal instruction in SDMA command stream\n");
			/* XXX check the bitfield order! */
			me_id = (ring_id & 0x3) >> 0;
			queue_id = (ring_id & 0xc) >> 2;
			switch (me_id) {
			case 0:
				switch (queue_id) {
				case 0:
					queue_reset = true;
					break;
				case 1:
					/* XXX compute */
					queue_reset = true;
					break;
				case 2:
					/* XXX compute */
					queue_reset = true;
					break;
				}
				break;
			case 1:
				switch (queue_id) {
				case 0:
					queue_reset = true;
					break;
				case 1:
					/* XXX compute */
					queue_reset = true;
					break;
				case 2:
					/* XXX compute */
					queue_reset = true;
					break;
				}
				break;
			}
			break;
		default:
			DRM_DEBUG("Unhandled interrupt: %d %d\n", src_id, src_data);
			break;
		}

		/* wptr/rptr are in bytes! */
		rptr += 16;
		rptr &= rdev->ih.ptr_mask;
		WREG32(IH_RB_RPTR, rptr);
	}
	if (queue_dp)
		schedule_work(&rdev->dp_work);
	if (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	if (queue_reset) {
		rdev->needs_reset = true;
		wake_up_all(&rdev->fence_queue);
	}
	if (queue_thermal)
		schedule_work(&rdev->pm.dpm.thermal.work);
	rdev->ih.rptr = rptr;
	atomic_set(&rdev->ih.lock, 0);

	/* make sure wptr hasn't changed while processing */
	wptr = cik_get_ih_wptr(rdev);
	if (wptr != rptr)
		goto restart_ih;

	return IRQ_HANDLED;
}