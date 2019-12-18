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
typedef  int /*<<< orphan*/  u32 ;
struct mixer_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BIT_VP_ENABLED ; 
 int /*<<< orphan*/  MXR_CFG ; 
 int /*<<< orphan*/  MXR_CFG_GRP0_ENABLE ; 
 int /*<<< orphan*/  MXR_CFG_GRP1_ENABLE ; 
 int /*<<< orphan*/  MXR_CFG_VP_ENABLE ; 
 int /*<<< orphan*/  MXR_LAYER_CFG ; 
 int /*<<< orphan*/  MXR_LAYER_CFG_GRP0_MASK ; 
 int /*<<< orphan*/  MXR_LAYER_CFG_GRP0_VAL (unsigned int) ; 
 int /*<<< orphan*/  MXR_LAYER_CFG_GRP1_MASK ; 
 int /*<<< orphan*/  MXR_LAYER_CFG_GRP1_VAL (unsigned int) ; 
 int /*<<< orphan*/  MXR_LAYER_CFG_VP_MASK ; 
 int /*<<< orphan*/  MXR_LAYER_CFG_VP_VAL (unsigned int) ; 
#define  VP_DEFAULT_WIN 128 
 int /*<<< orphan*/  VP_ENABLE ; 
 int /*<<< orphan*/  VP_ENABLE_ON ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_cfg_layer(struct mixer_context *ctx, unsigned int win,
			    unsigned int priority, bool enable)
{
	u32 val = enable ? ~0 : 0;

	switch (win) {
	case 0:
		mixer_reg_writemask(ctx, MXR_CFG, val, MXR_CFG_GRP0_ENABLE);
		mixer_reg_writemask(ctx, MXR_LAYER_CFG,
				    MXR_LAYER_CFG_GRP0_VAL(priority),
				    MXR_LAYER_CFG_GRP0_MASK);
		break;
	case 1:
		mixer_reg_writemask(ctx, MXR_CFG, val, MXR_CFG_GRP1_ENABLE);
		mixer_reg_writemask(ctx, MXR_LAYER_CFG,
				    MXR_LAYER_CFG_GRP1_VAL(priority),
				    MXR_LAYER_CFG_GRP1_MASK);

		break;
	case VP_DEFAULT_WIN:
		if (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags)) {
			vp_reg_writemask(ctx, VP_ENABLE, val, VP_ENABLE_ON);
			mixer_reg_writemask(ctx, MXR_CFG, val,
				MXR_CFG_VP_ENABLE);
			mixer_reg_writemask(ctx, MXR_LAYER_CFG,
					    MXR_LAYER_CFG_VP_VAL(priority),
					    MXR_LAYER_CFG_VP_MASK);
		}
		break;
	}
}