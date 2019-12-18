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
typedef  scalar_t__ u16 ;
struct fm10k_vf_info {scalar_t__ pf_vid; scalar_t__ sw_vid; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_ERR_PARAM ; 

s32 fm10k_iov_select_vid(struct fm10k_vf_info *vf_info, u16 vid)
{
	if (!vid)
		return vf_info->pf_vid ? vf_info->pf_vid : vf_info->sw_vid;
	else if (vf_info->pf_vid && vid != vf_info->pf_vid)
		return FM10K_ERR_PARAM;
	else
		return vid;
}