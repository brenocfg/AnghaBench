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
struct input_event {scalar_t__ type; scalar_t__ code; scalar_t__ value; int /*<<< orphan*/  input_event_usec; int /*<<< orphan*/  input_event_sec; } ;
struct evdev_client {int head; int bufsize; int tail; int packet_head; int /*<<< orphan*/  fasync; struct input_event* buffer; } ;

/* Variables and functions */
 scalar_t__ EV_SYN ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 scalar_t__ SYN_DROPPED ; 
 scalar_t__ SYN_REPORT ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __pass_event(struct evdev_client *client,
			 const struct input_event *event)
{
	client->buffer[client->head++] = *event;
	client->head &= client->bufsize - 1;

	if (unlikely(client->head == client->tail)) {
		/*
		 * This effectively "drops" all unconsumed events, leaving
		 * EV_SYN/SYN_DROPPED plus the newest event in the queue.
		 */
		client->tail = (client->head - 2) & (client->bufsize - 1);

		client->buffer[client->tail].input_event_sec =
						event->input_event_sec;
		client->buffer[client->tail].input_event_usec =
						event->input_event_usec;
		client->buffer[client->tail].type = EV_SYN;
		client->buffer[client->tail].code = SYN_DROPPED;
		client->buffer[client->tail].value = 0;

		client->packet_head = client->tail;
	}

	if (event->type == EV_SYN && event->code == SYN_REPORT) {
		client->packet_head = client->head;
		kill_fasync(&client->fasync, SIGIO, POLL_IN);
	}
}