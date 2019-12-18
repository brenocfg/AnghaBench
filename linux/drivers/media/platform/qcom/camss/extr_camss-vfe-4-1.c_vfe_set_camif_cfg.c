#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vfe_line {TYPE_1__* fmt; } ;
struct vfe_device {scalar_t__ base; } ;
struct TYPE_2__ {int code; int width; int height; } ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_UYVY8_2X8 131 
#define  MEDIA_BUS_FMT_VYUY8_2X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 size_t MSM_VFE_PAD_SINK ; 
 scalar_t__ VFE_0_CAMIF_CFG ; 
 int VFE_0_CAMIF_CFG_VFE_OUTPUT_EN ; 
 scalar_t__ VFE_0_CAMIF_FRAME_CFG ; 
 scalar_t__ VFE_0_CAMIF_IRQ_SUBSAMPLE_PATTERN ; 
 scalar_t__ VFE_0_CAMIF_SUBSAMPLE_CFG_0 ; 
 scalar_t__ VFE_0_CAMIF_WINDOW_HEIGHT_CFG ; 
 scalar_t__ VFE_0_CAMIF_WINDOW_WIDTH_CFG ; 
 scalar_t__ VFE_0_CORE_CFG ; 
 int VFE_0_CORE_CFG_PIXEL_PATTERN_CBYCRY ; 
 int VFE_0_CORE_CFG_PIXEL_PATTERN_CRYCBY ; 
 int VFE_0_CORE_CFG_PIXEL_PATTERN_YCBYCR ; 
 int VFE_0_CORE_CFG_PIXEL_PATTERN_YCRYCB ; 
 int /*<<< orphan*/  VFE_0_RDI_CFG_x (int /*<<< orphan*/ ) ; 
 int VFE_0_RDI_CFG_x_MIPI_EN_BITS ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vfe_set_camif_cfg(struct vfe_device *vfe, struct vfe_line *line)
{
	u32 val;

	switch (line->fmt[MSM_VFE_PAD_SINK].code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_YCBYCR;
		break;
	case MEDIA_BUS_FMT_YVYU8_2X8:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_YCRYCB;
		break;
	case MEDIA_BUS_FMT_UYVY8_2X8:
	default:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_CBYCRY;
		break;
	case MEDIA_BUS_FMT_VYUY8_2X8:
		val = VFE_0_CORE_CFG_PIXEL_PATTERN_CRYCBY;
		break;
	}

	writel_relaxed(val, vfe->base + VFE_0_CORE_CFG);

	val = line->fmt[MSM_VFE_PAD_SINK].width * 2;
	val |= line->fmt[MSM_VFE_PAD_SINK].height << 16;
	writel_relaxed(val, vfe->base + VFE_0_CAMIF_FRAME_CFG);

	val = line->fmt[MSM_VFE_PAD_SINK].width * 2 - 1;
	writel_relaxed(val, vfe->base + VFE_0_CAMIF_WINDOW_WIDTH_CFG);

	val = line->fmt[MSM_VFE_PAD_SINK].height - 1;
	writel_relaxed(val, vfe->base + VFE_0_CAMIF_WINDOW_HEIGHT_CFG);

	val = 0xffffffff;
	writel_relaxed(val, vfe->base + VFE_0_CAMIF_SUBSAMPLE_CFG_0);

	val = 0xffffffff;
	writel_relaxed(val, vfe->base + VFE_0_CAMIF_IRQ_SUBSAMPLE_PATTERN);

	val = VFE_0_RDI_CFG_x_MIPI_EN_BITS;
	vfe_reg_set(vfe, VFE_0_RDI_CFG_x(0), val);

	val = VFE_0_CAMIF_CFG_VFE_OUTPUT_EN;
	writel_relaxed(val, vfe->base + VFE_0_CAMIF_CFG);
}