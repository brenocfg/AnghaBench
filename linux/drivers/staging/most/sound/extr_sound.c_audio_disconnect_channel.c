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
struct sound_adapter {int /*<<< orphan*/  dev_list; } ;
struct most_interface {struct sound_adapter* priv; } ;
struct channel {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 struct channel* get_channel (struct most_interface*,int) ; 
 int /*<<< orphan*/  kfree (struct channel*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  release_adapter (struct sound_adapter*) ; 

__attribute__((used)) static int audio_disconnect_channel(struct most_interface *iface,
				    int channel_id)
{
	struct channel *channel;
	struct sound_adapter *adpt = iface->priv;

	channel = get_channel(iface, channel_id);
	if (!channel) {
		pr_err("sound_disconnect_channel(), invalid channel %d\n",
		       channel_id);
		return -EINVAL;
	}

	list_del(&channel->list);

	kfree(channel);
	if (list_empty(&adpt->dev_list))
		release_adapter(adpt);
	return 0;
}