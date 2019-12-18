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
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct input_event {int input_event_usec; scalar_t__ value; int /*<<< orphan*/  code; int /*<<< orphan*/  type; int /*<<< orphan*/  input_event_sec; } ;
struct evdev_client {size_t clk_type; int head; int bufsize; int tail; int packet_head; struct input_event* buffer; TYPE_2__* evdev; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SYN ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  SYN_DROPPED ; 
 int /*<<< orphan*/ * input_get_timestamp (int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __evdev_queue_syn_dropped(struct evdev_client *client)
{
	ktime_t *ev_time = input_get_timestamp(client->evdev->handle.dev);
	struct timespec64 ts = ktime_to_timespec64(ev_time[client->clk_type]);
	struct input_event ev;

	ev.input_event_sec = ts.tv_sec;
	ev.input_event_usec = ts.tv_nsec / NSEC_PER_USEC;
	ev.type = EV_SYN;
	ev.code = SYN_DROPPED;
	ev.value = 0;

	client->buffer[client->head++] = ev;
	client->head &= client->bufsize - 1;

	if (unlikely(client->head == client->tail)) {
		/* drop queue but keep our SYN_DROPPED event */
		client->tail = (client->head - 1) & (client->bufsize - 1);
		client->packet_head = client->tail;
	}
}