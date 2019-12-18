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
struct vlv_s0ix_state {void* clock_gate_dis2; void* pcbr; void* gu_ctl1; void* gu_ctl0; void* pmwgicz; void* gtlc_survive; void* gtlc_wake_ctrl; void* gt_fifoctl; void* tilectl; void** gt_scratch; void* pm_ier; void* pm_imr; void* gt_ier; void* gt_imr; void* spare2gh; void* rcedata; void* rcubmabdtmr; void* rp_deucsw; void* rp_down_timeout; void* pwrdwnupctl; void* ecobus; void* rpdeuc; void* rpdeuhwtc; void* gfxpause; void* misccpctl; void* rstctl; void* rcgctl2; void* rcgctl1; void* ucgctl3; void* ucgctl1; void* mbctl; void* gsckgctl; void* g3dctl; void* tlb_rd_addr; void* blt_hwsp; void* bsd_hwsp; void* ecochk; void* render_hwsp; void* gfx_max_req_count; void* media_max_req_count; void** lra_limits; void* gfx_pend_tlb1; void* gfx_pend_tlb0; void* arb_mode; void* gfx_prio_ctrl; void* wr_watermark; } ;
struct drm_i915_private {struct vlv_s0ix_state* vlv_s0ix_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_MODE ; 
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  BLT_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  BSD_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  ECOBUS ; 
 int /*<<< orphan*/  GAM_ECOCHK ; 
 int /*<<< orphan*/  GEN6_GFXPAUSE ; 
 int /*<<< orphan*/  GEN6_MBCTL ; 
 int /*<<< orphan*/  GEN6_PMIER ; 
 int /*<<< orphan*/  GEN6_PMIMR ; 
 int /*<<< orphan*/  GEN6_RCGCTL1 ; 
 int /*<<< orphan*/  GEN6_RCGCTL2 ; 
 int /*<<< orphan*/  GEN6_RCUBMABDTMR ; 
 int /*<<< orphan*/  GEN6_RPDEUC ; 
 int /*<<< orphan*/  GEN6_RPDEUCSW ; 
 int /*<<< orphan*/  GEN6_RPDEUHWTC ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_TIMEOUT ; 
 int /*<<< orphan*/  GEN6_RSTCTL ; 
 int /*<<< orphan*/  GEN6_UCGCTL1 ; 
 int /*<<< orphan*/  GEN6_UCGCTL3 ; 
 int /*<<< orphan*/  GEN7_GFX_MAX_REQ_COUNT ; 
 int /*<<< orphan*/  GEN7_GFX_PEND_TLB0 ; 
 int /*<<< orphan*/  GEN7_GFX_PEND_TLB1 ; 
 int /*<<< orphan*/  GEN7_GFX_PRIO_CTRL ; 
 int /*<<< orphan*/  GEN7_GT_SCRATCH (int) ; 
 int /*<<< orphan*/  GEN7_LRA_LIMITS (int) ; 
 int /*<<< orphan*/  GEN7_MEDIA_MAX_REQ_COUNT ; 
 int /*<<< orphan*/  GEN7_MISCCPCTL ; 
 int /*<<< orphan*/  GEN7_TLB_RD_ADDR ; 
 int /*<<< orphan*/  GEN7_WR_WATERMARK ; 
 int /*<<< orphan*/  GTFIFOCTL ; 
 int /*<<< orphan*/  GTIER ; 
 int /*<<< orphan*/  GTIMR ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RENDER_HWS_PGA_GEN7 ; 
 int /*<<< orphan*/  TILECTL ; 
 int /*<<< orphan*/  VLV_G3DCTL ; 
 int /*<<< orphan*/  VLV_GSCKGCTL ; 
 int /*<<< orphan*/  VLV_GTLC_SURVIVABILITY_REG ; 
 int /*<<< orphan*/  VLV_GTLC_WAKE_CTRL ; 
 int /*<<< orphan*/  VLV_GUNIT_CLOCK_GATE2 ; 
 int /*<<< orphan*/  VLV_GU_CTL0 ; 
 int /*<<< orphan*/  VLV_GU_CTL1 ; 
 int /*<<< orphan*/  VLV_PCBR ; 
 int /*<<< orphan*/  VLV_PMWGICZ ; 
 int /*<<< orphan*/  VLV_PWRDWNUPCTL ; 
 int /*<<< orphan*/  VLV_RCEDATA ; 
 int /*<<< orphan*/  VLV_SPAREG2H ; 

__attribute__((used)) static void vlv_save_gunit_s0ix_state(struct drm_i915_private *dev_priv)
{
	struct vlv_s0ix_state *s = dev_priv->vlv_s0ix_state;
	int i;

	if (!s)
		return;

	/* GAM 0x4000-0x4770 */
	s->wr_watermark		= I915_READ(GEN7_WR_WATERMARK);
	s->gfx_prio_ctrl	= I915_READ(GEN7_GFX_PRIO_CTRL);
	s->arb_mode		= I915_READ(ARB_MODE);
	s->gfx_pend_tlb0	= I915_READ(GEN7_GFX_PEND_TLB0);
	s->gfx_pend_tlb1	= I915_READ(GEN7_GFX_PEND_TLB1);

	for (i = 0; i < ARRAY_SIZE(s->lra_limits); i++)
		s->lra_limits[i] = I915_READ(GEN7_LRA_LIMITS(i));

	s->media_max_req_count	= I915_READ(GEN7_MEDIA_MAX_REQ_COUNT);
	s->gfx_max_req_count	= I915_READ(GEN7_GFX_MAX_REQ_COUNT);

	s->render_hwsp		= I915_READ(RENDER_HWS_PGA_GEN7);
	s->ecochk		= I915_READ(GAM_ECOCHK);
	s->bsd_hwsp		= I915_READ(BSD_HWS_PGA_GEN7);
	s->blt_hwsp		= I915_READ(BLT_HWS_PGA_GEN7);

	s->tlb_rd_addr		= I915_READ(GEN7_TLB_RD_ADDR);

	/* MBC 0x9024-0x91D0, 0x8500 */
	s->g3dctl		= I915_READ(VLV_G3DCTL);
	s->gsckgctl		= I915_READ(VLV_GSCKGCTL);
	s->mbctl		= I915_READ(GEN6_MBCTL);

	/* GCP 0x9400-0x9424, 0x8100-0x810C */
	s->ucgctl1		= I915_READ(GEN6_UCGCTL1);
	s->ucgctl3		= I915_READ(GEN6_UCGCTL3);
	s->rcgctl1		= I915_READ(GEN6_RCGCTL1);
	s->rcgctl2		= I915_READ(GEN6_RCGCTL2);
	s->rstctl		= I915_READ(GEN6_RSTCTL);
	s->misccpctl		= I915_READ(GEN7_MISCCPCTL);

	/* GPM 0xA000-0xAA84, 0x8000-0x80FC */
	s->gfxpause		= I915_READ(GEN6_GFXPAUSE);
	s->rpdeuhwtc		= I915_READ(GEN6_RPDEUHWTC);
	s->rpdeuc		= I915_READ(GEN6_RPDEUC);
	s->ecobus		= I915_READ(ECOBUS);
	s->pwrdwnupctl		= I915_READ(VLV_PWRDWNUPCTL);
	s->rp_down_timeout	= I915_READ(GEN6_RP_DOWN_TIMEOUT);
	s->rp_deucsw		= I915_READ(GEN6_RPDEUCSW);
	s->rcubmabdtmr		= I915_READ(GEN6_RCUBMABDTMR);
	s->rcedata		= I915_READ(VLV_RCEDATA);
	s->spare2gh		= I915_READ(VLV_SPAREG2H);

	/* Display CZ domain, 0x4400C-0x4402C, 0x4F000-0x4F11F */
	s->gt_imr		= I915_READ(GTIMR);
	s->gt_ier		= I915_READ(GTIER);
	s->pm_imr		= I915_READ(GEN6_PMIMR);
	s->pm_ier		= I915_READ(GEN6_PMIER);

	for (i = 0; i < ARRAY_SIZE(s->gt_scratch); i++)
		s->gt_scratch[i] = I915_READ(GEN7_GT_SCRATCH(i));

	/* GT SA CZ domain, 0x100000-0x138124 */
	s->tilectl		= I915_READ(TILECTL);
	s->gt_fifoctl		= I915_READ(GTFIFOCTL);
	s->gtlc_wake_ctrl	= I915_READ(VLV_GTLC_WAKE_CTRL);
	s->gtlc_survive		= I915_READ(VLV_GTLC_SURVIVABILITY_REG);
	s->pmwgicz		= I915_READ(VLV_PMWGICZ);

	/* Gunit-Display CZ domain, 0x182028-0x1821CF */
	s->gu_ctl0		= I915_READ(VLV_GU_CTL0);
	s->gu_ctl1		= I915_READ(VLV_GU_CTL1);
	s->pcbr			= I915_READ(VLV_PCBR);
	s->clock_gate_dis2	= I915_READ(VLV_GUNIT_CLOCK_GATE2);

	/*
	 * Not saving any of:
	 * DFT,		0x9800-0x9EC0
	 * SARB,	0xB000-0xB1FC
	 * GAC,		0x5208-0x524C, 0x14000-0x14C000
	 * PCI CFG
	 */
}