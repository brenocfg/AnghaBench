#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct output {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct host1x_channel {TYPE_2__ cdma; TYPE_1__* dev; } ;
struct host1x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_show_channel_cdma (struct host1x*,struct host1x_channel*,struct output*) ; 
 int /*<<< orphan*/  host1x_hw_show_channel_fifo (struct host1x*,struct host1x_channel*,struct output*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int show_channel(struct host1x_channel *ch, void *data, bool show_fifo)
{
	struct host1x *m = dev_get_drvdata(ch->dev->parent);
	struct output *o = data;

	mutex_lock(&ch->cdma.lock);

	if (show_fifo)
		host1x_hw_show_channel_fifo(m, ch, o);

	host1x_hw_show_channel_cdma(m, ch, o);

	mutex_unlock(&ch->cdma.lock);

	return 0;
}