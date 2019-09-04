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

/* Variables and functions */
 int EINVAL ; 
#define  IPUV3_CHANNEL_G_MEM_IC_PP 134 
#define  IPUV3_CHANNEL_G_MEM_IC_PRP_VF 133 
#define  IPUV3_CHANNEL_MEM_BG_ASYNC 132 
#define  IPUV3_CHANNEL_MEM_BG_SYNC 131 
#define  IPUV3_CHANNEL_MEM_FG_ASYNC 130 
#define  IPUV3_CHANNEL_MEM_FG_SYNC 129 
#define  IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB 128 

__attribute__((used)) static int ipu_channel_albm(int ch_num)
{
	switch (ch_num) {
	case IPUV3_CHANNEL_G_MEM_IC_PRP_VF:	return 0;
	case IPUV3_CHANNEL_G_MEM_IC_PP:		return 1;
	case IPUV3_CHANNEL_MEM_FG_SYNC:		return 2;
	case IPUV3_CHANNEL_MEM_FG_ASYNC:	return 3;
	case IPUV3_CHANNEL_MEM_BG_SYNC:		return 4;
	case IPUV3_CHANNEL_MEM_BG_ASYNC:	return 5;
	case IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB: return 6;
	default:
		return -EINVAL;
	}
}