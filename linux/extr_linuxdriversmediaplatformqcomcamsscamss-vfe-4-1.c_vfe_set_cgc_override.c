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
typedef  int /*<<< orphan*/  u32 ;
struct vfe_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_CGC_OVERRIDE_1 ; 
 int /*<<< orphan*/  VFE_0_CGC_OVERRIDE_1_IMAGE_Mx_CGC_OVERRIDE (scalar_t__) ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void vfe_set_cgc_override(struct vfe_device *vfe, u8 wm, u8 enable)
{
	u32 val = VFE_0_CGC_OVERRIDE_1_IMAGE_Mx_CGC_OVERRIDE(wm);

	if (enable)
		vfe_reg_set(vfe, VFE_0_CGC_OVERRIDE_1, val);
	else
		vfe_reg_clr(vfe, VFE_0_CGC_OVERRIDE_1, val);

	wmb();
}