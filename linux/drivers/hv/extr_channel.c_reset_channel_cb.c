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
struct vmbus_channel {int /*<<< orphan*/ * onchannel_callback; } ;

/* Variables and functions */

__attribute__((used)) static void reset_channel_cb(void *arg)
{
	struct vmbus_channel *channel = arg;

	channel->onchannel_callback = NULL;
}