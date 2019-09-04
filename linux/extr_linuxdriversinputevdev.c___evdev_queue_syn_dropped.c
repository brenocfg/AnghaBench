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
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct input_event {int input_event_usec; scalar_t__ value; int /*<<< orphan*/  code; int /*<<< orphan*/  type; int /*<<< orphan*/  input_event_sec; } ;
struct evdev_client {scalar_t__ clk_type; int head; int bufsize; int tail; int packet_head; struct input_event* buffer; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ EV_CLK_MONO ; 
 scalar_t__ EV_CLK_REAL ; 
 int /*<<< orphan*/  EV_SYN ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  SYN_DROPPED ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __evdev_queue_syn_dropped(struct evdev_client *client)
{
	struct input_event ev;
	ktime_t time;
	struct timespec64 ts;

	time = client->clk_type == EV_CLK_REAL ?
			ktime_get_real() :
			client->clk_type == EV_CLK_MONO ?
				ktime_get() :
				ktime_get_boottime();

	ts = ktime_to_timespec64(time);
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