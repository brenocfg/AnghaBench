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
struct mixer_context {scalar_t__ mxr_ver; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BIT_VP_ENABLED ; 
 int /*<<< orphan*/  MXR_CFG ; 
 int /*<<< orphan*/  MXR_CFG_LAYER_UPDATE ; 
 int /*<<< orphan*/  MXR_STATUS ; 
 int /*<<< orphan*/  MXR_STATUS_SYNC_ENABLE ; 
 scalar_t__ MXR_VER_128_0_0_184 ; 
 scalar_t__ MXR_VER_16_0_33_0 ; 
 int /*<<< orphan*/  VP_SHADOW_UPDATE ; 
 int /*<<< orphan*/  VP_SHADOW_UPDATE_ENABLE ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp_reg_write (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_enable_sync(struct mixer_context *ctx)
{
	if (ctx->mxr_ver == MXR_VER_16_0_33_0 ||
	    ctx->mxr_ver == MXR_VER_128_0_0_184)
		mixer_reg_writemask(ctx, MXR_CFG, ~0, MXR_CFG_LAYER_UPDATE);
	mixer_reg_writemask(ctx, MXR_STATUS, ~0, MXR_STATUS_SYNC_ENABLE);
	if (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags))
		vp_reg_write(ctx, VP_SHADOW_UPDATE, VP_SHADOW_UPDATE_ENABLE);
}