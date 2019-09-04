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
struct host1x_channel_list {struct host1x_channel* channels; int /*<<< orphan*/  allocated_channels; } ;
struct host1x_channel {unsigned int id; } ;
struct host1x {int /*<<< orphan*/  dev; TYPE_1__* info; struct host1x_channel_list channel_list; } ;
struct TYPE_2__ {unsigned int nb_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct host1x_channel *acquire_unused_channel(struct host1x *host)
{
	struct host1x_channel_list *chlist = &host->channel_list;
	unsigned int max_channels = host->info->nb_channels;
	unsigned int index;

	index = find_first_zero_bit(chlist->allocated_channels, max_channels);
	if (index >= max_channels) {
		dev_err(host->dev, "failed to find free channel\n");
		return NULL;
	}

	chlist->channels[index].id = index;

	set_bit(index, chlist->allocated_channels);

	return &chlist->channels[index];
}