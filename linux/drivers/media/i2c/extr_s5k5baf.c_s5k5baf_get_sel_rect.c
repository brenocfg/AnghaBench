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
typedef  int u32 ;
typedef  enum selection_rect { ____Placeholder_selection_rect } selection_rect ;

/* Variables and functions */
 int R_CIS ; 
 int R_COMPOSE ; 
 int R_CROP_SINK ; 
 int R_CROP_SOURCE ; 
 int R_INVALID ; 
#define  V4L2_SEL_TGT_COMPOSE 131 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 130 
#define  V4L2_SEL_TGT_CROP 129 
#define  V4L2_SEL_TGT_CROP_BOUNDS 128 

__attribute__((used)) static enum selection_rect s5k5baf_get_sel_rect(u32 pad, u32 target)
{
	switch (target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
		return pad ? R_COMPOSE : R_CIS;
	case V4L2_SEL_TGT_CROP:
		return pad ? R_CROP_SOURCE : R_CROP_SINK;
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		return pad ? R_INVALID : R_CROP_SINK;
	case V4L2_SEL_TGT_COMPOSE:
		return pad ? R_INVALID : R_COMPOSE;
	default:
		return R_INVALID;
	}
}