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
struct pp_smu_funcs {int dummy; } ;
struct hw_asic_id {int chip_family; int /*<<< orphan*/  hw_internal_rev; } ;
struct dccg {int dummy; } ;
struct dc_context {struct hw_asic_id asic_id; } ;
struct clk_mgr {int dummy; } ;
struct clk_mgr_internal {struct clk_mgr base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASICREV_IS_PICASSO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASICREV_IS_RAVEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASICREV_IS_RAVEN2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASICREV_IS_RENOIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASICREV_IS_VEGA20_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_FIJI_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS10_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS11_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_POLARIS12_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_TONGA_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC_REV_IS_VEGAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  FAMILY_AI 134 
#define  FAMILY_CI 133 
#define  FAMILY_CZ 132 
#define  FAMILY_KV 131 
#define  FAMILY_NV 130 
#define  FAMILY_RV 129 
#define  FAMILY_VI 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dce110_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  dce112_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  dce120_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  dce121_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  dce_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*) ; 
 int /*<<< orphan*/  dcn20_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*,struct pp_smu_funcs*,struct dccg*) ; 
 struct clk_mgr_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rn_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*,struct pp_smu_funcs*,struct dccg*) ; 
 int /*<<< orphan*/  rv1_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*,struct pp_smu_funcs*) ; 
 int /*<<< orphan*/  rv2_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*,struct pp_smu_funcs*) ; 

struct clk_mgr *dc_clk_mgr_create(struct dc_context *ctx, struct pp_smu_funcs *pp_smu, struct dccg *dccg)
{
	struct hw_asic_id asic_id = ctx->asic_id;

	struct clk_mgr_internal *clk_mgr = kzalloc(sizeof(*clk_mgr), GFP_KERNEL);

	if (clk_mgr == NULL) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	switch (asic_id.chip_family) {
	case FAMILY_CI:
	case FAMILY_KV:
		dce_clk_mgr_construct(ctx, clk_mgr);
		break;
	case FAMILY_CZ:
		dce110_clk_mgr_construct(ctx, clk_mgr);
		break;
	case FAMILY_VI:
		if (ASIC_REV_IS_TONGA_P(asic_id.hw_internal_rev) ||
				ASIC_REV_IS_FIJI_P(asic_id.hw_internal_rev)) {
			dce_clk_mgr_construct(ctx, clk_mgr);
			break;
		}
		if (ASIC_REV_IS_POLARIS10_P(asic_id.hw_internal_rev) ||
				ASIC_REV_IS_POLARIS11_M(asic_id.hw_internal_rev) ||
				ASIC_REV_IS_POLARIS12_V(asic_id.hw_internal_rev)) {
			dce112_clk_mgr_construct(ctx, clk_mgr);
			break;
		}
		if (ASIC_REV_IS_VEGAM(asic_id.hw_internal_rev)) {
			dce112_clk_mgr_construct(ctx, clk_mgr);
			break;
		}
		break;
	case FAMILY_AI:
		if (ASICREV_IS_VEGA20_P(asic_id.hw_internal_rev))
			dce121_clk_mgr_construct(ctx, clk_mgr);
		else
			dce120_clk_mgr_construct(ctx, clk_mgr);
		break;

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case FAMILY_RV:
#if defined(CONFIG_DRM_AMD_DC_DCN2_1)
		if (ASICREV_IS_RENOIR(asic_id.hw_internal_rev)) {
			rn_clk_mgr_construct(ctx, clk_mgr, pp_smu, dccg);
			break;
		}
#endif	/* DCN2_1 */
		if (ASICREV_IS_RAVEN2(asic_id.hw_internal_rev)) {
			rv2_clk_mgr_construct(ctx, clk_mgr, pp_smu);
			break;
		}
		if (ASICREV_IS_RAVEN(asic_id.hw_internal_rev) ||
				ASICREV_IS_PICASSO(asic_id.hw_internal_rev)) {
			rv1_clk_mgr_construct(ctx, clk_mgr, pp_smu);
			break;
		}
		break;
#endif	/* Family RV */

#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	case FAMILY_NV:
		dcn20_clk_mgr_construct(ctx, clk_mgr, pp_smu, dccg);
		break;
#endif /* Family NV */

	default:
		ASSERT(0); /* Unknown Asic */
		break;
	}

	return &clk_mgr->base;
}