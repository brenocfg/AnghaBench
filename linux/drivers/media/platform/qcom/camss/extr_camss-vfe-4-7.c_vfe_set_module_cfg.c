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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct vfe_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_MODULE_LENS_EN ; 
 int VFE_0_MODULE_LENS_EN_CHROMA_UPSAMPLE ; 
 int VFE_0_MODULE_LENS_EN_DEMUX ; 
 int /*<<< orphan*/  VFE_0_MODULE_ZOOM_EN ; 
 int VFE_0_MODULE_ZOOM_EN_CROP_ENC ; 
 int VFE_0_MODULE_ZOOM_EN_SCALE_ENC ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vfe_set_module_cfg(struct vfe_device *vfe, u8 enable)
{
	u32 val_lens = VFE_0_MODULE_LENS_EN_DEMUX |
		       VFE_0_MODULE_LENS_EN_CHROMA_UPSAMPLE;
	u32 val_zoom = VFE_0_MODULE_ZOOM_EN_SCALE_ENC |
		       VFE_0_MODULE_ZOOM_EN_CROP_ENC;

	if (enable) {
		vfe_reg_set(vfe, VFE_0_MODULE_LENS_EN, val_lens);
		vfe_reg_set(vfe, VFE_0_MODULE_ZOOM_EN, val_zoom);
	} else {
		vfe_reg_clr(vfe, VFE_0_MODULE_LENS_EN, val_lens);
		vfe_reg_clr(vfe, VFE_0_MODULE_ZOOM_EN, val_zoom);
	}
}