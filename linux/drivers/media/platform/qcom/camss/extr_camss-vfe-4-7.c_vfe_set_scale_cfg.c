#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_12__ {int width; int height; } ;
struct TYPE_7__ {int pixelformat; } ;
struct TYPE_8__ {TYPE_1__ pix_mp; } ;
struct TYPE_9__ {TYPE_2__ fmt; } ;
struct TYPE_10__ {TYPE_3__ active_fmt; } ;
struct vfe_line {TYPE_6__ compose; TYPE_5__* fmt; TYPE_4__ video_out; } ;
struct vfe_device {scalar_t__ base; } ;
struct TYPE_11__ {int width; int height; } ;

/* Variables and functions */
 size_t MSM_VFE_PAD_SINK ; 
 int V4L2_PIX_FMT_NV12 ; 
 int V4L2_PIX_FMT_NV21 ; 
 scalar_t__ VFE_0_SCALE_ENC_CBCR_CFG ; 
 scalar_t__ VFE_0_SCALE_ENC_CBCR_H_IMAGE_SIZE ; 
 scalar_t__ VFE_0_SCALE_ENC_CBCR_H_PHASE ; 
 scalar_t__ VFE_0_SCALE_ENC_CBCR_V_IMAGE_SIZE ; 
 scalar_t__ VFE_0_SCALE_ENC_CBCR_V_PHASE ; 
 scalar_t__ VFE_0_SCALE_ENC_Y_CFG ; 
 scalar_t__ VFE_0_SCALE_ENC_Y_H_IMAGE_SIZE ; 
 scalar_t__ VFE_0_SCALE_ENC_Y_H_PHASE ; 
 scalar_t__ VFE_0_SCALE_ENC_Y_V_IMAGE_SIZE ; 
 scalar_t__ VFE_0_SCALE_ENC_Y_V_PHASE ; 
 int vfe_calc_interp_reso (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vfe_set_scale_cfg(struct vfe_device *vfe, struct vfe_line *line)
{
	u32 p = line->video_out.active_fmt.fmt.pix_mp.pixelformat;
	u32 reg;
	u16 input, output;
	u8 interp_reso;
	u32 phase_mult;

	writel_relaxed(0x3, vfe->base + VFE_0_SCALE_ENC_Y_CFG);

	input = line->fmt[MSM_VFE_PAD_SINK].width - 1;
	output = line->compose.width - 1;
	reg = (output << 16) | input;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_H_IMAGE_SIZE);

	interp_reso = vfe_calc_interp_reso(input, output);
	phase_mult = input * (1 << (14 + interp_reso)) / output;
	reg = (interp_reso << 28) | phase_mult;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_H_PHASE);

	input = line->fmt[MSM_VFE_PAD_SINK].height - 1;
	output = line->compose.height - 1;
	reg = (output << 16) | input;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_V_IMAGE_SIZE);

	interp_reso = vfe_calc_interp_reso(input, output);
	phase_mult = input * (1 << (14 + interp_reso)) / output;
	reg = (interp_reso << 28) | phase_mult;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_Y_V_PHASE);

	writel_relaxed(0x3, vfe->base + VFE_0_SCALE_ENC_CBCR_CFG);

	input = line->fmt[MSM_VFE_PAD_SINK].width - 1;
	output = line->compose.width / 2 - 1;
	reg = (output << 16) | input;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_H_IMAGE_SIZE);

	interp_reso = vfe_calc_interp_reso(input, output);
	phase_mult = input * (1 << (14 + interp_reso)) / output;
	reg = (interp_reso << 28) | phase_mult;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_H_PHASE);

	input = line->fmt[MSM_VFE_PAD_SINK].height - 1;
	output = line->compose.height - 1;
	if (p == V4L2_PIX_FMT_NV12 || p == V4L2_PIX_FMT_NV21)
		output = line->compose.height / 2 - 1;
	reg = (output << 16) | input;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_V_IMAGE_SIZE);

	interp_reso = vfe_calc_interp_reso(input, output);
	phase_mult = input * (1 << (14 + interp_reso)) / output;
	reg = (interp_reso << 28) | phase_mult;
	writel_relaxed(reg, vfe->base + VFE_0_SCALE_ENC_CBCR_V_PHASE);
}