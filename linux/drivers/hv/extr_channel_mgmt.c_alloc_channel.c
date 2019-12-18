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
struct vmbus_channel {int /*<<< orphan*/  callback_event; int /*<<< orphan*/  percpu_list; int /*<<< orphan*/  sc_list; int /*<<< orphan*/  rescind_event; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_ringbuffer_pre_init (struct vmbus_channel*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct vmbus_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vmbus_on_event ; 

__attribute__((used)) static struct vmbus_channel *alloc_channel(void)
{
	struct vmbus_channel *channel;

	channel = kzalloc(sizeof(*channel), GFP_ATOMIC);
	if (!channel)
		return NULL;

	spin_lock_init(&channel->lock);
	init_completion(&channel->rescind_event);

	INIT_LIST_HEAD(&channel->sc_list);
	INIT_LIST_HEAD(&channel->percpu_list);

	tasklet_init(&channel->callback_event,
		     vmbus_on_event, (unsigned long)channel);

	hv_ringbuffer_pre_init(channel);

	return channel;
}