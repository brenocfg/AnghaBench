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
struct tw686x_video_channel {TYPE_1__* dma_descs; } ;
struct tw686x_dev {struct tw686x_video_channel* video_channels; } ;
struct TYPE_2__ {unsigned int size; } ;

/* Variables and functions */
 unsigned int TW686X_SG_TABLE_SIZE ; 
 scalar_t__ is_second_gen (struct tw686x_dev*) ; 
 unsigned int max_channels (struct tw686x_dev*) ; 

__attribute__((used)) static int tw686x_sg_setup(struct tw686x_dev *dev)
{
	unsigned int sg_table_size, pb, ch, channels;

	if (is_second_gen(dev)) {
		/*
		 * TW6865/TW6869: each channel needs a pair of
		 * P-B descriptor tables.
		 */
		channels = max_channels(dev);
		sg_table_size = TW686X_SG_TABLE_SIZE;
	} else {
		/*
		 * TW6864/TW6868: we need to allocate a pair of
		 * P-B descriptor tables, common for all channels.
		 * Each table will be bigger than 4 KB.
		 */
		channels = 1;
		sg_table_size = max_channels(dev) * TW686X_SG_TABLE_SIZE;
	}

	for (ch = 0; ch < channels; ch++) {
		struct tw686x_video_channel *vc = &dev->video_channels[ch];

		for (pb = 0; pb < 2; pb++)
			vc->dma_descs[pb].size = sg_table_size;
	}

	return 0;
}