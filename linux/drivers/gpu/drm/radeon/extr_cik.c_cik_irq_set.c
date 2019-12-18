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
struct radeon_ring {int me; int pipe; } ;
struct TYPE_3__ {scalar_t__* hpd; int /*<<< orphan*/ * pflip; scalar_t__* crtc_vblank_int; int /*<<< orphan*/ * ring_int; int /*<<< orphan*/  installed; } ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;
struct radeon_device {int num_crtc; TYPE_1__ irq; struct radeon_ring* ring; TYPE_2__ ih; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int CNTX_BUSY_INT_ENABLE ; 
 int CNTX_EMPTY_INT_ENABLE ; 
 scalar_t__ CP_INT_CNTL_RING0 ; 
 scalar_t__ CP_ME1_PIPE0_INT_CNTL ; 
 scalar_t__ CP_ME1_PIPE1_INT_CNTL ; 
 scalar_t__ CP_ME1_PIPE2_INT_CNTL ; 
 scalar_t__ CP_ME1_PIPE3_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE0_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE1_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE2_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE3_INT_CNTL ; 
 scalar_t__ DC_HPD1_INT_CONTROL ; 
 scalar_t__ DC_HPD2_INT_CONTROL ; 
 scalar_t__ DC_HPD3_INT_CONTROL ; 
 scalar_t__ DC_HPD4_INT_CONTROL ; 
 scalar_t__ DC_HPD5_INT_CONTROL ; 
 scalar_t__ DC_HPD6_INT_CONTROL ; 
 int DC_HPDx_INT_EN ; 
 int DC_HPDx_RX_INT_EN ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 scalar_t__ EVERGREEN_CRTC0_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC1_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC2_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC3_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC4_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC5_REGISTER_OFFSET ; 
 scalar_t__ GRBM_INT_CNTL ; 
 scalar_t__ GRPH_INT_CONTROL ; 
 int GRPH_PFLIP_INT_MASK ; 
 scalar_t__ LB_INTERRUPT_MASK ; 
 int PRIV_INSTR_INT_ENABLE ; 
 int PRIV_REG_INT_ENABLE ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ SDMA0_CNTL ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 scalar_t__ SRBM_STATUS ; 
 int TIME_STAMP_INT_ENABLE ; 
 int TRAP_ENABLE ; 
 int VBLANK_INTERRUPT_MASK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cik_disable_interrupt_state (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_disable_interrupts (struct radeon_device*) ; 

int cik_irq_set(struct radeon_device *rdev)
{
	u32 cp_int_cntl;
	u32 cp_m1p0, cp_m1p1, cp_m1p2, cp_m1p3;
	u32 cp_m2p0, cp_m2p1, cp_m2p2, cp_m2p3;
	u32 crtc1 = 0, crtc2 = 0, crtc3 = 0, crtc4 = 0, crtc5 = 0, crtc6 = 0;
	u32 hpd1, hpd2, hpd3, hpd4, hpd5, hpd6;
	u32 grbm_int_cntl = 0;
	u32 dma_cntl, dma_cntl1;

	if (!rdev->irq.installed) {
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		return -EINVAL;
	}
	/* don't enable anything if the ih is disabled */
	if (!rdev->ih.enabled) {
		cik_disable_interrupts(rdev);
		/* force the active interrupt state to all disabled */
		cik_disable_interrupt_state(rdev);
		return 0;
	}

	cp_int_cntl = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	cp_int_cntl |= PRIV_INSTR_INT_ENABLE | PRIV_REG_INT_ENABLE;

	hpd1 = RREG32(DC_HPD1_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd2 = RREG32(DC_HPD2_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd3 = RREG32(DC_HPD3_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd4 = RREG32(DC_HPD4_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd5 = RREG32(DC_HPD5_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);
	hpd6 = RREG32(DC_HPD6_INT_CONTROL) & ~(DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN);

	dma_cntl = RREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	dma_cntl1 = RREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;

	cp_m1p0 = RREG32(CP_ME1_PIPE0_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m1p1 = RREG32(CP_ME1_PIPE1_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m1p2 = RREG32(CP_ME1_PIPE2_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m1p3 = RREG32(CP_ME1_PIPE3_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p0 = RREG32(CP_ME2_PIPE0_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p1 = RREG32(CP_ME2_PIPE1_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p2 = RREG32(CP_ME2_PIPE2_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;
	cp_m2p3 = RREG32(CP_ME2_PIPE3_INT_CNTL) & ~TIME_STAMP_INT_ENABLE;

	/* enable CP interrupts on all rings */
	if (atomic_read(&rdev->irq.ring_int[RADEON_RING_TYPE_GFX_INDEX])) {
		DRM_DEBUG("cik_irq_set: sw int gfx\n");
		cp_int_cntl |= TIME_STAMP_INT_ENABLE;
	}
	if (atomic_read(&rdev->irq.ring_int[CAYMAN_RING_TYPE_CP1_INDEX])) {
		struct radeon_ring *ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
		DRM_DEBUG("si_irq_set: sw int cp1\n");
		if (ring->me == 1) {
			switch (ring->pipe) {
			case 0:
				cp_m1p0 |= TIME_STAMP_INT_ENABLE;
				break;
			case 1:
				cp_m1p1 |= TIME_STAMP_INT_ENABLE;
				break;
			case 2:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				break;
			case 3:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				break;
			default:
				DRM_DEBUG("si_irq_set: sw int cp1 invalid pipe %d\n", ring->pipe);
				break;
			}
		} else if (ring->me == 2) {
			switch (ring->pipe) {
			case 0:
				cp_m2p0 |= TIME_STAMP_INT_ENABLE;
				break;
			case 1:
				cp_m2p1 |= TIME_STAMP_INT_ENABLE;
				break;
			case 2:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				break;
			case 3:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				break;
			default:
				DRM_DEBUG("si_irq_set: sw int cp1 invalid pipe %d\n", ring->pipe);
				break;
			}
		} else {
			DRM_DEBUG("si_irq_set: sw int cp1 invalid me %d\n", ring->me);
		}
	}
	if (atomic_read(&rdev->irq.ring_int[CAYMAN_RING_TYPE_CP2_INDEX])) {
		struct radeon_ring *ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
		DRM_DEBUG("si_irq_set: sw int cp2\n");
		if (ring->me == 1) {
			switch (ring->pipe) {
			case 0:
				cp_m1p0 |= TIME_STAMP_INT_ENABLE;
				break;
			case 1:
				cp_m1p1 |= TIME_STAMP_INT_ENABLE;
				break;
			case 2:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				break;
			case 3:
				cp_m1p2 |= TIME_STAMP_INT_ENABLE;
				break;
			default:
				DRM_DEBUG("si_irq_set: sw int cp2 invalid pipe %d\n", ring->pipe);
				break;
			}
		} else if (ring->me == 2) {
			switch (ring->pipe) {
			case 0:
				cp_m2p0 |= TIME_STAMP_INT_ENABLE;
				break;
			case 1:
				cp_m2p1 |= TIME_STAMP_INT_ENABLE;
				break;
			case 2:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				break;
			case 3:
				cp_m2p2 |= TIME_STAMP_INT_ENABLE;
				break;
			default:
				DRM_DEBUG("si_irq_set: sw int cp2 invalid pipe %d\n", ring->pipe);
				break;
			}
		} else {
			DRM_DEBUG("si_irq_set: sw int cp2 invalid me %d\n", ring->me);
		}
	}

	if (atomic_read(&rdev->irq.ring_int[R600_RING_TYPE_DMA_INDEX])) {
		DRM_DEBUG("cik_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	}

	if (atomic_read(&rdev->irq.ring_int[CAYMAN_RING_TYPE_DMA1_INDEX])) {
		DRM_DEBUG("cik_irq_set: sw int dma1\n");
		dma_cntl1 |= TRAP_ENABLE;
	}

	if (rdev->irq.crtc_vblank_int[0] ||
	    atomic_read(&rdev->irq.pflip[0])) {
		DRM_DEBUG("cik_irq_set: vblank 0\n");
		crtc1 |= VBLANK_INTERRUPT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[1] ||
	    atomic_read(&rdev->irq.pflip[1])) {
		DRM_DEBUG("cik_irq_set: vblank 1\n");
		crtc2 |= VBLANK_INTERRUPT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[2] ||
	    atomic_read(&rdev->irq.pflip[2])) {
		DRM_DEBUG("cik_irq_set: vblank 2\n");
		crtc3 |= VBLANK_INTERRUPT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[3] ||
	    atomic_read(&rdev->irq.pflip[3])) {
		DRM_DEBUG("cik_irq_set: vblank 3\n");
		crtc4 |= VBLANK_INTERRUPT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[4] ||
	    atomic_read(&rdev->irq.pflip[4])) {
		DRM_DEBUG("cik_irq_set: vblank 4\n");
		crtc5 |= VBLANK_INTERRUPT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[5] ||
	    atomic_read(&rdev->irq.pflip[5])) {
		DRM_DEBUG("cik_irq_set: vblank 5\n");
		crtc6 |= VBLANK_INTERRUPT_MASK;
	}
	if (rdev->irq.hpd[0]) {
		DRM_DEBUG("cik_irq_set: hpd 1\n");
		hpd1 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	}
	if (rdev->irq.hpd[1]) {
		DRM_DEBUG("cik_irq_set: hpd 2\n");
		hpd2 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	}
	if (rdev->irq.hpd[2]) {
		DRM_DEBUG("cik_irq_set: hpd 3\n");
		hpd3 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	}
	if (rdev->irq.hpd[3]) {
		DRM_DEBUG("cik_irq_set: hpd 4\n");
		hpd4 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	}
	if (rdev->irq.hpd[4]) {
		DRM_DEBUG("cik_irq_set: hpd 5\n");
		hpd5 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	}
	if (rdev->irq.hpd[5]) {
		DRM_DEBUG("cik_irq_set: hpd 6\n");
		hpd6 |= DC_HPDx_INT_EN | DC_HPDx_RX_INT_EN;
	}

	WREG32(CP_INT_CNTL_RING0, cp_int_cntl);

	WREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET, dma_cntl);
	WREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET, dma_cntl1);

	WREG32(CP_ME1_PIPE0_INT_CNTL, cp_m1p0);
	WREG32(CP_ME1_PIPE1_INT_CNTL, cp_m1p1);
	WREG32(CP_ME1_PIPE2_INT_CNTL, cp_m1p2);
	WREG32(CP_ME1_PIPE3_INT_CNTL, cp_m1p3);
	WREG32(CP_ME2_PIPE0_INT_CNTL, cp_m2p0);
	WREG32(CP_ME2_PIPE1_INT_CNTL, cp_m2p1);
	WREG32(CP_ME2_PIPE2_INT_CNTL, cp_m2p2);
	WREG32(CP_ME2_PIPE3_INT_CNTL, cp_m2p3);

	WREG32(GRBM_INT_CNTL, grbm_int_cntl);

	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC0_REGISTER_OFFSET, crtc1);
	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC1_REGISTER_OFFSET, crtc2);
	if (rdev->num_crtc >= 4) {
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC2_REGISTER_OFFSET, crtc3);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC3_REGISTER_OFFSET, crtc4);
	}
	if (rdev->num_crtc >= 6) {
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC4_REGISTER_OFFSET, crtc5);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC5_REGISTER_OFFSET, crtc6);
	}

	if (rdev->num_crtc >= 2) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
	}
	if (rdev->num_crtc >= 4) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
	}
	if (rdev->num_crtc >= 6) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET,
		       GRPH_PFLIP_INT_MASK);
	}

	WREG32(DC_HPD1_INT_CONTROL, hpd1);
	WREG32(DC_HPD2_INT_CONTROL, hpd2);
	WREG32(DC_HPD3_INT_CONTROL, hpd3);
	WREG32(DC_HPD4_INT_CONTROL, hpd4);
	WREG32(DC_HPD5_INT_CONTROL, hpd5);
	WREG32(DC_HPD6_INT_CONTROL, hpd6);

	/* posting read */
	RREG32(SRBM_STATUS);

	return 0;
}