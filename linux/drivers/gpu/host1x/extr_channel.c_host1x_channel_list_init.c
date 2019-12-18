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
struct host1x_channel_list {void* allocated_channels; void* channels; } ;
struct host1x_channel {int dummy; } ;

/* Variables and functions */
 unsigned int BITS_TO_LONGS (unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_zero (void*,unsigned int) ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

int host1x_channel_list_init(struct host1x_channel_list *chlist,
			     unsigned int num_channels)
{
	chlist->channels = kcalloc(num_channels, sizeof(struct host1x_channel),
				   GFP_KERNEL);
	if (!chlist->channels)
		return -ENOMEM;

	chlist->allocated_channels =
		kcalloc(BITS_TO_LONGS(num_channels), sizeof(unsigned long),
			GFP_KERNEL);
	if (!chlist->allocated_channels) {
		kfree(chlist->channels);
		return -ENOMEM;
	}

	bitmap_zero(chlist->allocated_channels, num_channels);

	return 0;
}