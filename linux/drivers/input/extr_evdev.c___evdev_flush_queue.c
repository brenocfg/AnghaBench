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
struct input_event {unsigned int type; scalar_t__ code; } ;
struct evdev_client {int bufsize; unsigned int tail; unsigned int packet_head; unsigned int head; struct input_event* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int EV_SYN ; 
 scalar_t__ SYN_REPORT ; 

__attribute__((used)) static void __evdev_flush_queue(struct evdev_client *client, unsigned int type)
{
	unsigned int i, head, num;
	unsigned int mask = client->bufsize - 1;
	bool is_report;
	struct input_event *ev;

	BUG_ON(type == EV_SYN);

	head = client->tail;
	client->packet_head = client->tail;

	/* init to 1 so a leading SYN_REPORT will not be dropped */
	num = 1;

	for (i = client->tail; i != client->head; i = (i + 1) & mask) {
		ev = &client->buffer[i];
		is_report = ev->type == EV_SYN && ev->code == SYN_REPORT;

		if (ev->type == type) {
			/* drop matched entry */
			continue;
		} else if (is_report && !num) {
			/* drop empty SYN_REPORT groups */
			continue;
		} else if (head != i) {
			/* move entry to fill the gap */
			client->buffer[head] = *ev;
		}

		num++;
		head = (head + 1) & mask;

		if (is_report) {
			num = 0;
			client->packet_head = head;
		}
	}

	client->head = head;
}