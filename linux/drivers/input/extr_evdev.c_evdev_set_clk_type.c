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
struct evdev_client {int clk_type; scalar_t__ head; scalar_t__ tail; scalar_t__ packet_head; int /*<<< orphan*/  buffer_lock; } ;
typedef  enum input_clock_type { ____Placeholder_input_clock_type } input_clock_type ;

/* Variables and functions */
#define  CLOCK_BOOTTIME 130 
#define  CLOCK_MONOTONIC 129 
#define  CLOCK_REALTIME 128 
 int EINVAL ; 
 int INPUT_CLK_BOOT ; 
 int INPUT_CLK_MONO ; 
 int INPUT_CLK_REAL ; 
 int /*<<< orphan*/  __evdev_queue_syn_dropped (struct evdev_client*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int evdev_set_clk_type(struct evdev_client *client, unsigned int clkid)
{
	unsigned long flags;
	enum input_clock_type clk_type;

	switch (clkid) {

	case CLOCK_REALTIME:
		clk_type = INPUT_CLK_REAL;
		break;
	case CLOCK_MONOTONIC:
		clk_type = INPUT_CLK_MONO;
		break;
	case CLOCK_BOOTTIME:
		clk_type = INPUT_CLK_BOOT;
		break;
	default:
		return -EINVAL;
	}

	if (client->clk_type != clk_type) {
		client->clk_type = clk_type;

		/*
		 * Flush pending events and queue SYN_DROPPED event,
		 * but only if the queue is not empty.
		 */
		spin_lock_irqsave(&client->buffer_lock, flags);

		if (client->head != client->tail) {
			client->packet_head = client->head = client->tail;
			__evdev_queue_syn_dropped(client);
		}

		spin_unlock_irqrestore(&client->buffer_lock, flags);
	}

	return 0;
}