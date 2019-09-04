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
typedef  scalar_t__ u32 ;
struct mixer_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_VIDEO_CFG ; 
 int /*<<< orphan*/  mixer_reg_write (struct mixer_context*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mixer_cfg_vp_blend(struct mixer_context *ctx)
{
	u32 val;

	/*
	 * No blending at the moment since the NV12/NV21 pixelformats don't
	 * have an alpha channel. However the mixer supports a global alpha
	 * value for a layer. Once this functionality is exposed, we can
	 * support blending of the video layer through this.
	 */
	val = 0;
	mixer_reg_write(ctx, MXR_VIDEO_CFG, val);
}