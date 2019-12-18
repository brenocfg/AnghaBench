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
struct snd_pcm_substream {struct channel* private_data; } ;
struct channel {int /*<<< orphan*/  id; int /*<<< orphan*/  iface; int /*<<< orphan*/  playback_task; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ direction; } ;

/* Variables and functions */
 scalar_t__ MOST_CH_TX ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  most_stop_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcm_close(struct snd_pcm_substream *substream)
{
	struct channel *channel = substream->private_data;

	if (channel->cfg->direction == MOST_CH_TX)
		kthread_stop(channel->playback_task);
	most_stop_channel(channel->iface, channel->id, &comp);

	return 0;
}