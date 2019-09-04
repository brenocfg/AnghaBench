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
struct mixer_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_GRAPHIC_CFG (unsigned int) ; 
 int /*<<< orphan*/  MXR_GRP_CFG_BLEND_PRE_MUL ; 
 int /*<<< orphan*/  MXR_GRP_CFG_COLOR_KEY_DISABLE ; 
 int /*<<< orphan*/  MXR_GRP_CFG_MISC_MASK ; 
 int /*<<< orphan*/  MXR_GRP_CFG_PIXEL_BLEND_EN ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_cfg_gfx_blend(struct mixer_context *ctx, unsigned int win,
				bool alpha)
{
	u32 val;

	val  = MXR_GRP_CFG_COLOR_KEY_DISABLE; /* no blank key */
	if (alpha) {
		/* blending based on pixel alpha */
		val |= MXR_GRP_CFG_BLEND_PRE_MUL;
		val |= MXR_GRP_CFG_PIXEL_BLEND_EN;
	}
	mixer_reg_writemask(ctx, MXR_GRAPHIC_CFG(win),
			    val, MXR_GRP_CFG_MISC_MASK);
}