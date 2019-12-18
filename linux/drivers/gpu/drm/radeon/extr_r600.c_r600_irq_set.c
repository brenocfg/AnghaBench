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
struct TYPE_4__ {scalar_t__* afmt; scalar_t__* hpd; int /*<<< orphan*/ * pflip; scalar_t__* crtc_vblank_int; int /*<<< orphan*/ * ring_int; scalar_t__ dpm_thermal; int /*<<< orphan*/  installed; } ;
struct TYPE_3__ {int /*<<< orphan*/  enabled; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ irq; TYPE_1__ ih; } ;

/* Variables and functions */
 scalar_t__ AFMT_AUDIO_PACKET_CONTROL ; 
 int AFMT_AZ_FORMAT_WTRIG_MASK ; 
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE32 (struct radeon_device*) ; 
 scalar_t__ CG_THERMAL_INT ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ CHIP_RV770 ; 
 int CNTX_BUSY_INT_ENABLE ; 
 int CNTX_EMPTY_INT_ENABLE ; 
 scalar_t__ CP_INT_CNTL ; 
 scalar_t__ D1GRPH_INTERRUPT_CONTROL ; 
 int D1MODE_VBLANK_INT_MASK ; 
 scalar_t__ D2GRPH_INTERRUPT_CONTROL ; 
 int D2MODE_VBLANK_INT_MASK ; 
 scalar_t__ DCE3_HDMI1_AUDIO_PACKET_CONTROL ; 
 scalar_t__ DCE3_HDMI_OFFSET0 ; 
 scalar_t__ DCE3_HDMI_OFFSET1 ; 
 scalar_t__ DC_HOT_PLUG_DETECT1_INT_CONTROL ; 
 scalar_t__ DC_HOT_PLUG_DETECT2_INT_CONTROL ; 
 scalar_t__ DC_HOT_PLUG_DETECT3_INT_CONTROL ; 
 scalar_t__ DC_HPD1_INT_CONTROL ; 
 scalar_t__ DC_HPD2_INT_CONTROL ; 
 scalar_t__ DC_HPD3_INT_CONTROL ; 
 scalar_t__ DC_HPD4_INT_CONTROL ; 
 scalar_t__ DC_HPD5_INT_CONTROL ; 
 scalar_t__ DC_HPD6_INT_CONTROL ; 
 int DC_HPDx_INT_EN ; 
 scalar_t__ DMA_CNTL ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int DxGRPH_PFLIP_INT_MASK ; 
 scalar_t__ DxMODE_INT_MASK ; 
 int EINVAL ; 
 scalar_t__ GRBM_INT_CNTL ; 
 scalar_t__ HDMI0_AUDIO_PACKET_CONTROL ; 
 int HDMI0_AZ_FORMAT_WTRIG_MASK ; 
 scalar_t__ HDMI1_AUDIO_PACKET_CONTROL ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RB_INT_ENABLE ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ RV770_CG_THERMAL_INT ; 
 scalar_t__ R_000E50_SRBM_STATUS ; 
 int THERM_INT_MASK_HIGH ; 
 int THERM_INT_MASK_LOW ; 
 int TIME_STAMP_INT_ENABLE ; 
 int TRAP_ENABLE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r600_disable_interrupt_state (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_disable_interrupts (struct radeon_device*) ; 

int r600_irq_set(struct radeon_device *rdev)
{
	u32 cp_int_cntl = CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE;
	u32 mode_int = 0;
	u32 hpd1, hpd2, hpd3, hpd4 = 0, hpd5 = 0, hpd6 = 0;
	u32 grbm_int_cntl = 0;
	u32 hdmi0, hdmi1;
	u32 dma_cntl;
	u32 thermal_int = 0;

	if (!rdev->irq.installed) {
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		return -EINVAL;
	}
	/* don't enable anything if the ih is disabled */
	if (!rdev->ih.enabled) {
		r600_disable_interrupts(rdev);
		/* force the active interrupt state to all disabled */
		r600_disable_interrupt_state(rdev);
		return 0;
	}

	if (ASIC_IS_DCE3(rdev)) {
		hpd1 = RREG32(DC_HPD1_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd2 = RREG32(DC_HPD2_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd3 = RREG32(DC_HPD3_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd4 = RREG32(DC_HPD4_INT_CONTROL) & ~DC_HPDx_INT_EN;
		if (ASIC_IS_DCE32(rdev)) {
			hpd5 = RREG32(DC_HPD5_INT_CONTROL) & ~DC_HPDx_INT_EN;
			hpd6 = RREG32(DC_HPD6_INT_CONTROL) & ~DC_HPDx_INT_EN;
			hdmi0 = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
			hdmi1 = RREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
		} else {
			hdmi0 = RREG32(HDMI0_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
			hdmi1 = RREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
		}
	} else {
		hpd1 = RREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd2 = RREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hpd3 = RREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL) & ~DC_HPDx_INT_EN;
		hdmi0 = RREG32(HDMI0_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
		hdmi1 = RREG32(HDMI1_AUDIO_PACKET_CONTROL) & ~HDMI0_AZ_FORMAT_WTRIG_MASK;
	}

	dma_cntl = RREG32(DMA_CNTL) & ~TRAP_ENABLE;

	if ((rdev->family > CHIP_R600) && (rdev->family < CHIP_RV770)) {
		thermal_int = RREG32(CG_THERMAL_INT) &
			~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);
	} else if (rdev->family >= CHIP_RV770) {
		thermal_int = RREG32(RV770_CG_THERMAL_INT) &
			~(THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW);
	}
	if (rdev->irq.dpm_thermal) {
		DRM_DEBUG("dpm thermal\n");
		thermal_int |= THERM_INT_MASK_HIGH | THERM_INT_MASK_LOW;
	}

	if (atomic_read(&rdev->irq.ring_int[RADEON_RING_TYPE_GFX_INDEX])) {
		DRM_DEBUG("r600_irq_set: sw int\n");
		cp_int_cntl |= RB_INT_ENABLE;
		cp_int_cntl |= TIME_STAMP_INT_ENABLE;
	}

	if (atomic_read(&rdev->irq.ring_int[R600_RING_TYPE_DMA_INDEX])) {
		DRM_DEBUG("r600_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	}

	if (rdev->irq.crtc_vblank_int[0] ||
	    atomic_read(&rdev->irq.pflip[0])) {
		DRM_DEBUG("r600_irq_set: vblank 0\n");
		mode_int |= D1MODE_VBLANK_INT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[1] ||
	    atomic_read(&rdev->irq.pflip[1])) {
		DRM_DEBUG("r600_irq_set: vblank 1\n");
		mode_int |= D2MODE_VBLANK_INT_MASK;
	}
	if (rdev->irq.hpd[0]) {
		DRM_DEBUG("r600_irq_set: hpd 1\n");
		hpd1 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[1]) {
		DRM_DEBUG("r600_irq_set: hpd 2\n");
		hpd2 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[2]) {
		DRM_DEBUG("r600_irq_set: hpd 3\n");
		hpd3 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[3]) {
		DRM_DEBUG("r600_irq_set: hpd 4\n");
		hpd4 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[4]) {
		DRM_DEBUG("r600_irq_set: hpd 5\n");
		hpd5 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[5]) {
		DRM_DEBUG("r600_irq_set: hpd 6\n");
		hpd6 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.afmt[0]) {
		DRM_DEBUG("r600_irq_set: hdmi 0\n");
		hdmi0 |= HDMI0_AZ_FORMAT_WTRIG_MASK;
	}
	if (rdev->irq.afmt[1]) {
		DRM_DEBUG("r600_irq_set: hdmi 0\n");
		hdmi1 |= HDMI0_AZ_FORMAT_WTRIG_MASK;
	}

	WREG32(CP_INT_CNTL, cp_int_cntl);
	WREG32(DMA_CNTL, dma_cntl);
	WREG32(DxMODE_INT_MASK, mode_int);
	WREG32(D1GRPH_INTERRUPT_CONTROL, DxGRPH_PFLIP_INT_MASK);
	WREG32(D2GRPH_INTERRUPT_CONTROL, DxGRPH_PFLIP_INT_MASK);
	WREG32(GRBM_INT_CNTL, grbm_int_cntl);
	if (ASIC_IS_DCE3(rdev)) {
		WREG32(DC_HPD1_INT_CONTROL, hpd1);
		WREG32(DC_HPD2_INT_CONTROL, hpd2);
		WREG32(DC_HPD3_INT_CONTROL, hpd3);
		WREG32(DC_HPD4_INT_CONTROL, hpd4);
		if (ASIC_IS_DCE32(rdev)) {
			WREG32(DC_HPD5_INT_CONTROL, hpd5);
			WREG32(DC_HPD6_INT_CONTROL, hpd6);
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET0, hdmi0);
			WREG32(AFMT_AUDIO_PACKET_CONTROL + DCE3_HDMI_OFFSET1, hdmi1);
		} else {
			WREG32(HDMI0_AUDIO_PACKET_CONTROL, hdmi0);
			WREG32(DCE3_HDMI1_AUDIO_PACKET_CONTROL, hdmi1);
		}
	} else {
		WREG32(DC_HOT_PLUG_DETECT1_INT_CONTROL, hpd1);
		WREG32(DC_HOT_PLUG_DETECT2_INT_CONTROL, hpd2);
		WREG32(DC_HOT_PLUG_DETECT3_INT_CONTROL, hpd3);
		WREG32(HDMI0_AUDIO_PACKET_CONTROL, hdmi0);
		WREG32(HDMI1_AUDIO_PACKET_CONTROL, hdmi1);
	}
	if ((rdev->family > CHIP_R600) && (rdev->family < CHIP_RV770)) {
		WREG32(CG_THERMAL_INT, thermal_int);
	} else if (rdev->family >= CHIP_RV770) {
		WREG32(RV770_CG_THERMAL_INT, thermal_int);
	}

	/* posting read */
	RREG32(R_000E50_SRBM_STATUS);

	return 0;
}