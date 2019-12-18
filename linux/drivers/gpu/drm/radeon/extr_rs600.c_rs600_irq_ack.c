#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_4__ {int disp_int; int hdmi0_status; } ;
struct TYPE_5__ {TYPE_1__ r500; } ;
struct TYPE_6__ {TYPE_2__ stat_regs; } ;
struct radeon_device {TYPE_3__ irq; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE2 (struct radeon_device*) ; 
 scalar_t__ G_000044_DISPLAY_INT_STAT (int) ; 
 scalar_t__ G_007404_HDMI0_AZ_FORMAT_WTRIG (int) ; 
 scalar_t__ G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT (int) ; 
 scalar_t__ G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT (int) ; 
 scalar_t__ G_007EDC_LB_D1_VBLANK_INTERRUPT (int) ; 
 scalar_t__ G_007EDC_LB_D2_VBLANK_INTERRUPT (int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000044_GEN_INT_STATUS ; 
 int /*<<< orphan*/  R_006534_D1MODE_VBLANK_STATUS ; 
 int /*<<< orphan*/  R_006D34_D2MODE_VBLANK_STATUS ; 
 int /*<<< orphan*/  R_007404_HDMI0_STATUS ; 
 int /*<<< orphan*/  R_007408_HDMI0_AUDIO_PACKET_CONTROL ; 
 int /*<<< orphan*/  R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL ; 
 int /*<<< orphan*/  R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL ; 
 int /*<<< orphan*/  R_007EDC_DISP_INTERRUPT_STATUS ; 
 int S_000044_SW_INT (int) ; 
 int S_006534_D1MODE_VBLANK_ACK (int) ; 
 int S_006D34_D2MODE_VBLANK_ACK (int) ; 
 int S_007404_HDMI0_AZ_FORMAT_WTRIG (int) ; 
 int S_007408_HDMI0_AZ_FORMAT_WTRIG_ACK (int) ; 
 int S_007D08_DC_HOT_PLUG_DETECT1_INT_ACK (int) ; 
 int S_007D18_DC_HOT_PLUG_DETECT2_INT_ACK (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 rs600_irq_ack(struct radeon_device *rdev)
{
	uint32_t irqs = RREG32(R_000044_GEN_INT_STATUS);
	uint32_t irq_mask = S_000044_SW_INT(1);
	u32 tmp;

	if (G_000044_DISPLAY_INT_STAT(irqs)) {
		rdev->irq.stat_regs.r500.disp_int = RREG32(R_007EDC_DISP_INTERRUPT_STATUS);
		if (G_007EDC_LB_D1_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			WREG32(R_006534_D1MODE_VBLANK_STATUS,
				S_006534_D1MODE_VBLANK_ACK(1));
		}
		if (G_007EDC_LB_D2_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			WREG32(R_006D34_D2MODE_VBLANK_STATUS,
				S_006D34_D2MODE_VBLANK_ACK(1));
		}
		if (G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			tmp = RREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL);
			tmp |= S_007D08_DC_HOT_PLUG_DETECT1_INT_ACK(1);
			WREG32(R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL, tmp);
		}
		if (G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			tmp = RREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL);
			tmp |= S_007D18_DC_HOT_PLUG_DETECT2_INT_ACK(1);
			WREG32(R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL, tmp);
		}
	} else {
		rdev->irq.stat_regs.r500.disp_int = 0;
	}

	if (ASIC_IS_DCE2(rdev)) {
		rdev->irq.stat_regs.r500.hdmi0_status = RREG32(R_007404_HDMI0_STATUS) &
			S_007404_HDMI0_AZ_FORMAT_WTRIG(1);
		if (G_007404_HDMI0_AZ_FORMAT_WTRIG(rdev->irq.stat_regs.r500.hdmi0_status)) {
			tmp = RREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL);
			tmp |= S_007408_HDMI0_AZ_FORMAT_WTRIG_ACK(1);
			WREG32(R_007408_HDMI0_AUDIO_PACKET_CONTROL, tmp);
		}
	} else
		rdev->irq.stat_regs.r500.hdmi0_status = 0;

	if (irqs) {
		WREG32(R_000044_GEN_INT_STATUS, irqs);
	}
	return irqs & irq_mask;
}