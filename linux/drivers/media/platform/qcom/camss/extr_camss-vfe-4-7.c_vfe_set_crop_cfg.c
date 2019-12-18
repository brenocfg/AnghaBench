#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_10__ {int left; int width; int top; int height; } ;
struct TYPE_6__ {scalar_t__ pixelformat; } ;
struct TYPE_7__ {TYPE_1__ pix_mp; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct TYPE_9__ {TYPE_3__ active_fmt; } ;
struct vfe_line {TYPE_5__ crop; TYPE_4__ video_out; } ;
struct vfe_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_NV21 ; 
 scalar_t__ VFE_0_CROP_ENC_CBCR_HEIGHT ; 
 scalar_t__ VFE_0_CROP_ENC_CBCR_WIDTH ; 
 scalar_t__ VFE_0_CROP_ENC_Y_HEIGHT ; 
 scalar_t__ VFE_0_CROP_ENC_Y_WIDTH ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vfe_set_crop_cfg(struct vfe_device *vfe, struct vfe_line *line)
{
	u32 p = line->video_out.active_fmt.fmt.pix_mp.pixelformat;
	u32 reg;
	u16 first, last;

	first = line->crop.left;
	last = line->crop.left + line->crop.width - 1;
	reg = (first << 16) | last;
	writel_relaxed(reg, vfe->base + VFE_0_CROP_ENC_Y_WIDTH);

	first = line->crop.top;
	last = line->crop.top + line->crop.height - 1;
	reg = (first << 16) | last;
	writel_relaxed(reg, vfe->base + VFE_0_CROP_ENC_Y_HEIGHT);

	first = line->crop.left / 2;
	last = line->crop.left / 2 + line->crop.width / 2 - 1;
	reg = (first << 16) | last;
	writel_relaxed(reg, vfe->base + VFE_0_CROP_ENC_CBCR_WIDTH);

	first = line->crop.top;
	last = line->crop.top + line->crop.height - 1;
	if (p == V4L2_PIX_FMT_NV12 || p == V4L2_PIX_FMT_NV21) {
		first = line->crop.top / 2;
		last = line->crop.top / 2 + line->crop.height / 2 - 1;
	}
	reg = (first << 16) | last;
	writel_relaxed(reg, vfe->base + VFE_0_CROP_ENC_CBCR_HEIGHT);
}