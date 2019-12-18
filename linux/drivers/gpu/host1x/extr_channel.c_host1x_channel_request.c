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
struct host1x_channel_list {int /*<<< orphan*/  allocated_channels; } ;
struct host1x_channel {int /*<<< orphan*/  id; int /*<<< orphan*/  cdma; struct device* dev; int /*<<< orphan*/  submitlock; int /*<<< orphan*/  refcount; } ;
struct host1x {struct host1x_channel_list channel_list; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct host1x_channel* acquire_unused_channel (struct host1x*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int host1x_cdma_init (int /*<<< orphan*/ *) ; 
 int host1x_hw_channel_init (struct host1x*,struct host1x_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct host1x_channel *host1x_channel_request(struct device *dev)
{
	struct host1x *host = dev_get_drvdata(dev->parent);
	struct host1x_channel_list *chlist = &host->channel_list;
	struct host1x_channel *channel;
	int err;

	channel = acquire_unused_channel(host);
	if (!channel)
		return NULL;

	kref_init(&channel->refcount);
	mutex_init(&channel->submitlock);
	channel->dev = dev;

	err = host1x_hw_channel_init(host, channel, channel->id);
	if (err < 0)
		goto fail;

	err = host1x_cdma_init(&channel->cdma);
	if (err < 0)
		goto fail;

	return channel;

fail:
	clear_bit(channel->id, chlist->allocated_channels);

	dev_err(dev, "failed to initialize channel\n");

	return NULL;
}