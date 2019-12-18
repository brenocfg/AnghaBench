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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ V4L2_SEL_TGT_CROP_BOUNDS ; 
 scalar_t__ V4L2_SEL_TGT_CROP_DEFAULT ; 

__attribute__((used)) static inline bool mtk_mdp_is_target_crop(u32 target)
{
	if (target == V4L2_SEL_TGT_CROP_DEFAULT
	    || target == V4L2_SEL_TGT_CROP_BOUNDS
	    || target == V4L2_SEL_TGT_CROP)
		return true;
	return false;
}