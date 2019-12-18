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
struct mbo {int /*<<< orphan*/  hdm_channel_id; int /*<<< orphan*/  ifp; } ;
struct channel {int /*<<< orphan*/  substream; scalar_t__ is_stream_running; } ;

/* Variables and functions */
 int EINVAL ; 
 int copy_data (struct channel*,struct mbo*) ; 
 struct channel* get_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  most_put_mbo (struct mbo*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_rx_completion(struct mbo *mbo)
{
	struct channel *channel = get_channel(mbo->ifp, mbo->hdm_channel_id);
	bool period_elapsed = false;

	if (!channel) {
		pr_err("sound_rx_completion(), invalid channel %d\n",
		       mbo->hdm_channel_id);
		return -EINVAL;
	}

	if (channel->is_stream_running)
		period_elapsed = copy_data(channel, mbo);

	most_put_mbo(mbo);

	if (period_elapsed)
		snd_pcm_period_elapsed(channel->substream);

	return 0;
}