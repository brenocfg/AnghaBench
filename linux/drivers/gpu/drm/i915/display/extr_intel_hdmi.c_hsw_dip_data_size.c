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
#define  DP_SDP_PPS 129 
#define  DP_SDP_VSC 128 
 int VIDEO_DIP_DATA_SIZE ; 
 int VIDEO_DIP_PPS_DATA_SIZE ; 
 int VIDEO_DIP_VSC_DATA_SIZE ; 

__attribute__((used)) static int hsw_dip_data_size(unsigned int type)
{
	switch (type) {
	case DP_SDP_VSC:
		return VIDEO_DIP_VSC_DATA_SIZE;
	case DP_SDP_PPS:
		return VIDEO_DIP_PPS_DATA_SIZE;
	default:
		return VIDEO_DIP_DATA_SIZE;
	}
}