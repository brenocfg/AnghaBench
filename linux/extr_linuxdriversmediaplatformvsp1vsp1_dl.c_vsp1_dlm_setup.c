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
struct vsp1_device {TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int wpf_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_DL_CTRL ; 
 int VI6_DL_CTRL_AR_WAIT_SHIFT ; 
 int VI6_DL_CTRL_DC0 ; 
 int VI6_DL_CTRL_DC1 ; 
 int VI6_DL_CTRL_DC2 ; 
 int VI6_DL_CTRL_DLE ; 
 int /*<<< orphan*/  VI6_DL_EXT_CTRL (unsigned int) ; 
 int VI6_DL_EXT_CTRL_DLPRI ; 
 int VI6_DL_EXT_CTRL_EXT ; 
 int VI6_DL_EXT_CTRL_POLINT_SHIFT ; 
 int /*<<< orphan*/  VI6_DL_SWAP ; 
 int VI6_DL_SWAP_LWS ; 
 int /*<<< orphan*/  VSP1_HAS_EXT_DL ; 
 scalar_t__ vsp1_feature (struct vsp1_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_write (struct vsp1_device*,int /*<<< orphan*/ ,int) ; 

void vsp1_dlm_setup(struct vsp1_device *vsp1)
{
	unsigned int i;
	u32 ctrl = (256 << VI6_DL_CTRL_AR_WAIT_SHIFT)
		 | VI6_DL_CTRL_DC2 | VI6_DL_CTRL_DC1 | VI6_DL_CTRL_DC0
		 | VI6_DL_CTRL_DLE;
	u32 ext_dl = (0x02 << VI6_DL_EXT_CTRL_POLINT_SHIFT)
		   | VI6_DL_EXT_CTRL_DLPRI | VI6_DL_EXT_CTRL_EXT;

	if (vsp1_feature(vsp1, VSP1_HAS_EXT_DL)) {
		for (i = 0; i < vsp1->info->wpf_count; ++i)
			vsp1_write(vsp1, VI6_DL_EXT_CTRL(i), ext_dl);
	}

	vsp1_write(vsp1, VI6_DL_CTRL, ctrl);
	vsp1_write(vsp1, VI6_DL_SWAP, VI6_DL_SWAP_LWS);
}