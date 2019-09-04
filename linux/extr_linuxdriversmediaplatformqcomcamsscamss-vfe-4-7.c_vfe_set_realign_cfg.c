#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ pixelformat; } ;
struct TYPE_6__ {TYPE_1__ pix_mp; } ;
struct TYPE_7__ {TYPE_2__ fmt; } ;
struct TYPE_8__ {TYPE_3__ active_fmt; } ;
struct vfe_line {TYPE_4__ video_out; } ;
struct vfe_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_UYVY ; 
 scalar_t__ V4L2_PIX_FMT_VYUY ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 scalar_t__ V4L2_PIX_FMT_YVYU ; 
 int /*<<< orphan*/  VFE_0_MODULE_ZOOM_EN ; 
 scalar_t__ VFE_0_MODULE_ZOOM_EN_REALIGN_BUF ; 
 scalar_t__ VFE_0_REALIGN_BUF_CFG ; 
 scalar_t__ VFE_0_REALIGN_BUF_CFG_CB_ODD_PIXEL ; 
 scalar_t__ VFE_0_REALIGN_BUF_CFG_CR_ODD_PIXEL ; 
 scalar_t__ VFE_0_REALIGN_BUF_CFG_HSUB_ENABLE ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vfe_set_realign_cfg(struct vfe_device *vfe, struct vfe_line *line,
				u8 enable)
{
	u32 p = line->video_out.active_fmt.fmt.pix_mp.pixelformat;
	u32 val = VFE_0_MODULE_ZOOM_EN_REALIGN_BUF;

	if (p != V4L2_PIX_FMT_YUYV && p != V4L2_PIX_FMT_YVYU &&
			p != V4L2_PIX_FMT_VYUY && p != V4L2_PIX_FMT_UYVY)
		return;

	if (enable) {
		vfe_reg_set(vfe, VFE_0_MODULE_ZOOM_EN, val);
	} else {
		vfe_reg_clr(vfe, VFE_0_MODULE_ZOOM_EN, val);
		return;
	}

	val = VFE_0_REALIGN_BUF_CFG_HSUB_ENABLE;

	if (p == V4L2_PIX_FMT_UYVY || p == V4L2_PIX_FMT_YUYV)
		val |= VFE_0_REALIGN_BUF_CFG_CR_ODD_PIXEL;
	else
		val |= VFE_0_REALIGN_BUF_CFG_CB_ODD_PIXEL;

	writel_relaxed(val, vfe->base + VFE_0_REALIGN_BUF_CFG);
}