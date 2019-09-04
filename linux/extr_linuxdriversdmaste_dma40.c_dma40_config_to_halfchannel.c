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
struct stedma40_half_channel_info {int psize; int /*<<< orphan*/  flow_ctrl; } ;
struct d40_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STEDMA40_NO_FLOW_CTRL ; 
 int STEDMA40_PSIZE_LOG_1 ; 
 int STEDMA40_PSIZE_LOG_16 ; 
 int STEDMA40_PSIZE_LOG_4 ; 
 int STEDMA40_PSIZE_LOG_8 ; 
 int STEDMA40_PSIZE_PHY_1 ; 
 int STEDMA40_PSIZE_PHY_16 ; 
 int STEDMA40_PSIZE_PHY_4 ; 
 int STEDMA40_PSIZE_PHY_8 ; 
 scalar_t__ chan_is_logical (struct d40_chan*) ; 

__attribute__((used)) static int
dma40_config_to_halfchannel(struct d40_chan *d40c,
			    struct stedma40_half_channel_info *info,
			    u32 maxburst)
{
	int psize;

	if (chan_is_logical(d40c)) {
		if (maxburst >= 16)
			psize = STEDMA40_PSIZE_LOG_16;
		else if (maxburst >= 8)
			psize = STEDMA40_PSIZE_LOG_8;
		else if (maxburst >= 4)
			psize = STEDMA40_PSIZE_LOG_4;
		else
			psize = STEDMA40_PSIZE_LOG_1;
	} else {
		if (maxburst >= 16)
			psize = STEDMA40_PSIZE_PHY_16;
		else if (maxburst >= 8)
			psize = STEDMA40_PSIZE_PHY_8;
		else if (maxburst >= 4)
			psize = STEDMA40_PSIZE_PHY_4;
		else
			psize = STEDMA40_PSIZE_PHY_1;
	}

	info->psize = psize;
	info->flow_ctrl = STEDMA40_NO_FLOW_CTRL;

	return 0;
}