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
struct drm_device {int dummy; } ;

/* Variables and functions */
#define  HDMI 131 
#define  TC35876X 130 
#define  TMD_VID 129 
#define  TPO_VID 128 
 int /*<<< orphan*/  mdfld_dsi_output_init (struct drm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdfld_tc35876x_funcs ; 
 int /*<<< orphan*/  mdfld_tmd_vid_funcs ; 
 int /*<<< orphan*/  mdfld_tpo_vid_funcs ; 
 int /*<<< orphan*/  tc35876x_init (struct drm_device*) ; 

__attribute__((used)) static void mdfld_init_panel(struct drm_device *dev, int mipi_pipe,
								int p_type)
{
	switch (p_type) {
	case TPO_VID:
		mdfld_dsi_output_init(dev, mipi_pipe, &mdfld_tpo_vid_funcs);
		break;
	case TC35876X:
		tc35876x_init(dev);
		mdfld_dsi_output_init(dev, mipi_pipe, &mdfld_tc35876x_funcs);
		break;
	case TMD_VID:
		mdfld_dsi_output_init(dev, mipi_pipe, &mdfld_tmd_vid_funcs);
		break;
	case HDMI:
/*		if (dev_priv->mdfld_hdmi_present)
			mdfld_hdmi_init(dev, &dev_priv->mode_dev); */
		break;
	}
}