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
struct mixer_context {scalar_t__ mxr_ver; int /*<<< orphan*/  scan_value; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BIT_INTERLACE ; 
 int /*<<< orphan*/  MXR_CFG ; 
 int /*<<< orphan*/  MXR_CFG_SCAN_INTERLACE ; 
 int /*<<< orphan*/  MXR_CFG_SCAN_MASK ; 
 int /*<<< orphan*/  MXR_CFG_SCAN_PROGRESSIVE ; 
 int MXR_MXR_RES_HEIGHT (int) ; 
 int MXR_MXR_RES_WIDTH (int) ; 
 int /*<<< orphan*/  MXR_RESOLUTION ; 
 scalar_t__ MXR_VER_128_0_0_184 ; 
 int /*<<< orphan*/  mixer_reg_write (struct mixer_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_cfg_scan(struct mixer_context *ctx, int width, int height)
{
	u32 val;

	/* choosing between interlace and progressive mode */
	val = test_bit(MXR_BIT_INTERLACE, &ctx->flags) ?
		MXR_CFG_SCAN_INTERLACE : MXR_CFG_SCAN_PROGRESSIVE;

	if (ctx->mxr_ver == MXR_VER_128_0_0_184)
		mixer_reg_write(ctx, MXR_RESOLUTION,
			MXR_MXR_RES_HEIGHT(height) | MXR_MXR_RES_WIDTH(width));
	else
		val |= ctx->scan_value;

	mixer_reg_writemask(ctx, MXR_CFG, val, MXR_CFG_SCAN_MASK);
}