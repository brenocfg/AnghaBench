#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct TYPE_6__ {TYPE_2__* params; } ;
struct TYPE_4__ {unsigned int left; int width; unsigned int top; int height; } ;
struct isp_prev_device {TYPE_3__ params; TYPE_1__ crop; struct v4l2_mbus_framefmt* formats; } ;
struct isp_device {int dummy; } ;
struct TYPE_5__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_HORZ_INFO ; 
 unsigned int ISPPRV_HORZ_INFO_SPH_SHIFT ; 
 int /*<<< orphan*/  ISPPRV_VERT_INFO ; 
 unsigned int ISPPRV_VERT_INFO_SLV_SHIFT ; 
 scalar_t__ MEDIA_BUS_FMT_Y10_1X10 ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 
 int OMAP3ISP_PREV_CHROMA_SUPP ; 
 int OMAP3ISP_PREV_DEFECT_COR ; 
 int OMAP3ISP_PREV_HRZ_MED ; 
 int OMAP3ISP_PREV_LUMAENH ; 
 int OMAP3ISP_PREV_NF ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 size_t PREV_PAD_SINK ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void preview_config_input_size(struct isp_prev_device *prev, u32 active)
{
	const struct v4l2_mbus_framefmt *format = &prev->formats[PREV_PAD_SINK];
	struct isp_device *isp = to_isp_device(prev);
	unsigned int sph = prev->crop.left;
	unsigned int eph = prev->crop.left + prev->crop.width - 1;
	unsigned int slv = prev->crop.top;
	unsigned int elv = prev->crop.top + prev->crop.height - 1;
	u32 features;

	if (format->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    format->code != MEDIA_BUS_FMT_Y10_1X10) {
		sph -= 2;
		eph += 2;
		slv -= 2;
		elv += 2;
	}

	features = (prev->params.params[0].features & active)
		 | (prev->params.params[1].features & ~active);

	if (features & (OMAP3ISP_PREV_DEFECT_COR | OMAP3ISP_PREV_NF)) {
		sph -= 2;
		eph += 2;
		slv -= 2;
		elv += 2;
	}
	if (features & OMAP3ISP_PREV_HRZ_MED) {
		sph -= 2;
		eph += 2;
	}
	if (features & (OMAP3ISP_PREV_CHROMA_SUPP | OMAP3ISP_PREV_LUMAENH))
		sph -= 2;

	isp_reg_writel(isp, (sph << ISPPRV_HORZ_INFO_SPH_SHIFT) | eph,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_HORZ_INFO);
	isp_reg_writel(isp, (slv << ISPPRV_VERT_INFO_SLV_SHIFT) | elv,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_VERT_INFO);
}