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
typedef  unsigned int u32 ;
struct mixer_context {int dummy; } ;

/* Variables and functions */
 unsigned int DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  MXR_VIDEO_CFG ; 
 unsigned int MXR_VID_CFG_BLEND_EN ; 
 int /*<<< orphan*/  mixer_reg_write (struct mixer_context*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mixer_cfg_vp_blend(struct mixer_context *ctx, unsigned int alpha)
{
	u32 win_alpha = alpha >> 8;
	u32 val = 0;

	if (alpha != DRM_BLEND_ALPHA_OPAQUE) {
		val |= MXR_VID_CFG_BLEND_EN;
		val |= win_alpha;
	}
	mixer_reg_write(ctx, MXR_VIDEO_CFG, val);
}