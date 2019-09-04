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
#define  IPUV3_CHANNEL_MEM_BG_SYNC 130 
#define  IPUV3_CHANNEL_MEM_DC_SYNC 129 
#define  IPUV3_CHANNEL_MEM_FG_SYNC 128 

__attribute__((used)) static int ipu_chan_assign_axi_id(int ipu_chan)
{
	switch (ipu_chan) {
	case IPUV3_CHANNEL_MEM_BG_SYNC:
		return 1;
	case IPUV3_CHANNEL_MEM_FG_SYNC:
		return 2;
	case IPUV3_CHANNEL_MEM_DC_SYNC:
		return 3;
	default:
		return 0;
	}
}