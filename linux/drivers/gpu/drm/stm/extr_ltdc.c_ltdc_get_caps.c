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
struct TYPE_2__ {int bus_width; int hw_version; int non_alpha_only_l1; int pad_max_freq_hz; int /*<<< orphan*/  pix_fmt_hw; int /*<<< orphan*/  reg_ofs; int /*<<< orphan*/  nb_layers; } ;
struct ltdc_device {TYPE_1__ caps; int /*<<< orphan*/  regs; } ;
struct drm_device {struct ltdc_device* dev_private; } ;

/* Variables and functions */
 int ENODEV ; 
 int GC2R_BW ; 
#define  HWVER_10200 130 
#define  HWVER_10300 129 
#define  HWVER_20101 128 
 int /*<<< orphan*/  LTDC_GC2R ; 
 int /*<<< orphan*/  LTDC_IDR ; 
 int /*<<< orphan*/  LTDC_LCR ; 
 int /*<<< orphan*/  LTDC_MAX_LAYER ; 
 int /*<<< orphan*/  REG_OFS_4 ; 
 int /*<<< orphan*/  REG_OFS_NONE ; 
 int /*<<< orphan*/  clamp (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltdc_pix_fmt_a0 ; 
 int /*<<< orphan*/  ltdc_pix_fmt_a1 ; 
 void* reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltdc_get_caps(struct drm_device *ddev)
{
	struct ltdc_device *ldev = ddev->dev_private;
	u32 bus_width_log2, lcr, gc2r;

	/*
	 * at least 1 layer must be managed & the number of layers
	 * must not exceed LTDC_MAX_LAYER
	 */
	lcr = reg_read(ldev->regs, LTDC_LCR);

	ldev->caps.nb_layers = clamp((int)lcr, 1, LTDC_MAX_LAYER);

	/* set data bus width */
	gc2r = reg_read(ldev->regs, LTDC_GC2R);
	bus_width_log2 = (gc2r & GC2R_BW) >> 4;
	ldev->caps.bus_width = 8 << bus_width_log2;
	ldev->caps.hw_version = reg_read(ldev->regs, LTDC_IDR);

	switch (ldev->caps.hw_version) {
	case HWVER_10200:
	case HWVER_10300:
		ldev->caps.reg_ofs = REG_OFS_NONE;
		ldev->caps.pix_fmt_hw = ltdc_pix_fmt_a0;
		/*
		 * Hw older versions support non-alpha color formats derived
		 * from native alpha color formats only on the primary layer.
		 * For instance, RG16 native format without alpha works fine
		 * on 2nd layer but XR24 (derived color format from AR24)
		 * does not work on 2nd layer.
		 */
		ldev->caps.non_alpha_only_l1 = true;
		ldev->caps.pad_max_freq_hz = 90000000;
		if (ldev->caps.hw_version == HWVER_10200)
			ldev->caps.pad_max_freq_hz = 65000000;
		break;
	case HWVER_20101:
		ldev->caps.reg_ofs = REG_OFS_4;
		ldev->caps.pix_fmt_hw = ltdc_pix_fmt_a1;
		ldev->caps.non_alpha_only_l1 = false;
		ldev->caps.pad_max_freq_hz = 150000000;
		break;
	default:
		return -ENODEV;
	}

	return 0;
}