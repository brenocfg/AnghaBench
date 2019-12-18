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
struct mbo {int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  virt_address; } ;
struct channel {int /*<<< orphan*/  substream; scalar_t__ is_stream_running; int /*<<< orphan*/  id; int /*<<< orphan*/  iface; int /*<<< orphan*/  playback_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  comp ; 
 int copy_data (struct channel* const,struct mbo*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbo* most_get_mbo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  most_submit_mbo (struct mbo*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int playback_thread(void *data)
{
	struct channel *const channel = data;

	while (!kthread_should_stop()) {
		struct mbo *mbo = NULL;
		bool period_elapsed = false;

		wait_event_interruptible(
			channel->playback_waitq,
			kthread_should_stop() ||
			(channel->is_stream_running &&
			 (mbo = most_get_mbo(channel->iface, channel->id,
					     &comp))));
		if (!mbo)
			continue;

		if (channel->is_stream_running)
			period_elapsed = copy_data(channel, mbo);
		else
			memset(mbo->virt_address, 0, mbo->buffer_length);

		most_submit_mbo(mbo);
		if (period_elapsed)
			snd_pcm_period_elapsed(channel->substream);
	}

	return 0;
}