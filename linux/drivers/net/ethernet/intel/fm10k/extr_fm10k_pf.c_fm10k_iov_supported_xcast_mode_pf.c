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
typedef  int u8 ;
struct fm10k_vf_info {int vf_flags; } ;

/* Variables and functions */
 int FM10K_VF_FLAG_ALLMULTI_CAPABLE ; 
 int FM10K_VF_FLAG_MULTI_CAPABLE ; 
 int FM10K_VF_FLAG_NONE_CAPABLE ; 
 int FM10K_VF_FLAG_PROMISC_CAPABLE ; 
#define  FM10K_XCAST_MODE_ALLMULTI 131 
 int FM10K_XCAST_MODE_DISABLE ; 
#define  FM10K_XCAST_MODE_MULTI 130 
#define  FM10K_XCAST_MODE_NONE 129 
#define  FM10K_XCAST_MODE_PROMISC 128 

__attribute__((used)) static u8 fm10k_iov_supported_xcast_mode_pf(struct fm10k_vf_info *vf_info,
					    u8 mode)
{
	u8 vf_flags = vf_info->vf_flags;

	/* match up mode to capabilities as best as possible */
	switch (mode) {
	case FM10K_XCAST_MODE_PROMISC:
		if (vf_flags & FM10K_VF_FLAG_PROMISC_CAPABLE)
			return FM10K_XCAST_MODE_PROMISC;
		/* fall through */
	case FM10K_XCAST_MODE_ALLMULTI:
		if (vf_flags & FM10K_VF_FLAG_ALLMULTI_CAPABLE)
			return FM10K_XCAST_MODE_ALLMULTI;
		/* fall through */
	case FM10K_XCAST_MODE_MULTI:
		if (vf_flags & FM10K_VF_FLAG_MULTI_CAPABLE)
			return FM10K_XCAST_MODE_MULTI;
		/* fall through */
	case FM10K_XCAST_MODE_NONE:
		if (vf_flags & FM10K_VF_FLAG_NONE_CAPABLE)
			return FM10K_XCAST_MODE_NONE;
		/* fall through */
	default:
		break;
	}

	/* disable interface as it should not be able to request any */
	return FM10K_XCAST_MODE_DISABLE;
}