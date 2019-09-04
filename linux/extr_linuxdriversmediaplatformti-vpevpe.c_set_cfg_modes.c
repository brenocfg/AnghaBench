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
typedef  int /*<<< orphan*/  u32 ;
struct vpe_mmr_adb {int /*<<< orphan*/ * us3_regs; int /*<<< orphan*/ * us2_regs; int /*<<< orphan*/ * us1_regs; } ;
struct vpe_fmt {scalar_t__ fourcc; } ;
struct TYPE_3__ {struct vpe_mmr_adb* addr; } ;
struct vpe_ctx {int load_mmrs; TYPE_1__ mmr_adb; TYPE_2__* q_data; } ;
struct TYPE_4__ {struct vpe_fmt* fmt; } ;

/* Variables and functions */
 size_t Q_DATA_SRC ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  VPE_US_MODE_MASK ; 
 int /*<<< orphan*/  VPE_US_MODE_SHIFT ; 
 int /*<<< orphan*/  write_field (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_cfg_modes(struct vpe_ctx *ctx)
{
	struct vpe_fmt *fmt = ctx->q_data[Q_DATA_SRC].fmt;
	struct vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	u32 *us1_reg0 = &mmr_adb->us1_regs[0];
	u32 *us2_reg0 = &mmr_adb->us2_regs[0];
	u32 *us3_reg0 = &mmr_adb->us3_regs[0];
	int cfg_mode = 1;

	/*
	 * Cfg Mode 0: YUV420 source, enable upsampler, DEI is de-interlacing.
	 * Cfg Mode 1: YUV422 source, disable upsampler, DEI is de-interlacing.
	 */

	if (fmt->fourcc == V4L2_PIX_FMT_NV12)
		cfg_mode = 0;

	write_field(us1_reg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);
	write_field(us2_reg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);
	write_field(us3_reg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);

	ctx->load_mmrs = true;
}