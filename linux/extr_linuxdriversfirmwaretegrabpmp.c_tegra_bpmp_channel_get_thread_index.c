#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp_channel {struct tegra_bpmp* bpmp; } ;
struct tegra_bpmp {struct tegra_bpmp_channel* threaded_channels; TYPE_3__* soc; } ;
struct TYPE_4__ {unsigned int count; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;
struct TYPE_6__ {TYPE_2__ channels; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
tegra_bpmp_channel_get_thread_index(struct tegra_bpmp_channel *channel)
{
	struct tegra_bpmp *bpmp = channel->bpmp;
	unsigned int count;
	int index;

	count = bpmp->soc->channels.thread.count;

	index = channel - channel->bpmp->threaded_channels;
	if (index < 0 || index >= count)
		return -EINVAL;

	return index;
}