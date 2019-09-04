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
struct vop_win_data {TYPE_2__* phy; } ;
struct vop {int dummy; } ;
struct TYPE_4__ {TYPE_1__* scl; } ;
struct TYPE_3__ {scalar_t__ ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE_NONE ; 
 int /*<<< orphan*/  VOP_SCL_SET_EXT (struct vop*,struct vop_win_data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_WIN_SET (struct vop*,struct vop_win_data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbcr_hor_scl_mode ; 
 int /*<<< orphan*/  cbcr_ver_scl_mode ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  yrgb_hor_scl_mode ; 
 int /*<<< orphan*/  yrgb_ver_scl_mode ; 

__attribute__((used)) static void vop_win_disable(struct vop *vop, const struct vop_win_data *win)
{
	if (win->phy->scl && win->phy->scl->ext) {
		VOP_SCL_SET_EXT(vop, win, yrgb_hor_scl_mode, SCALE_NONE);
		VOP_SCL_SET_EXT(vop, win, yrgb_ver_scl_mode, SCALE_NONE);
		VOP_SCL_SET_EXT(vop, win, cbcr_hor_scl_mode, SCALE_NONE);
		VOP_SCL_SET_EXT(vop, win, cbcr_ver_scl_mode, SCALE_NONE);
	}

	VOP_WIN_SET(vop, win, enable, 0);
}