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
struct host1x_channel {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {struct host1x_channel* channels; } ;
struct host1x {TYPE_1__ channel_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 

struct host1x_channel *host1x_channel_get_index(struct host1x *host,
						unsigned int index)
{
	struct host1x_channel *ch = &host->channel_list.channels[index];

	if (!kref_get_unless_zero(&ch->refcount))
		return NULL;

	return ch;
}