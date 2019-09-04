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
struct vc_dmaman {int chan_available; int* has_feature; } ;

/* Variables and functions */
 int BCM_DMA_FEATURE_COUNT ; 
 int ENOENT ; 

__attribute__((used)) static int vc_dmaman_chan_alloc(struct vc_dmaman *dmaman,
				unsigned required_feature_set)
{
	u32 chans;
	int chan = 0;
	int feature;

	chans = dmaman->chan_available;
	for (feature = 0; feature < BCM_DMA_FEATURE_COUNT; feature++)
		/* select the subset of available channels with the desired
		   features */
		if (required_feature_set & (1 << feature))
			chans &= dmaman->has_feature[feature];

	if (!chans)
		return -ENOENT;

	/* return the ordinal of the first channel in the bitmap */
	while (chans != 0 && (chans & 1) == 0) {
		chans >>= 1;
		chan++;
	}
	/* claim the channel */
	dmaman->chan_available &= ~(1 << chan);

	return chan;
}