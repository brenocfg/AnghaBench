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
struct service_processor {int /*<<< orphan*/  lock; struct event_buffer* event_buffer; } ;
struct ibmasm_event {scalar_t__ serial_number; int data_size; int /*<<< orphan*/  data; } ;
struct event_reader {scalar_t__ next_serial_number; int data_size; int /*<<< orphan*/  data; scalar_t__ cancelled; int /*<<< orphan*/  wait; } ;
struct event_buffer {unsigned int next_index; struct ibmasm_event* events; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 unsigned int IBMASM_NUM_EVENTS ; 
 scalar_t__ event_available (struct event_buffer*,struct event_reader*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int ibmasm_get_next_event(struct service_processor *sp, struct event_reader *reader)
{
	struct event_buffer *buffer = sp->event_buffer;
	struct ibmasm_event *event;
	unsigned int index;
	unsigned long flags;

	reader->cancelled = 0;

	if (wait_event_interruptible(reader->wait,
			event_available(buffer, reader) || reader->cancelled))
		return -ERESTARTSYS;

	if (!event_available(buffer, reader))
		return 0;

	spin_lock_irqsave(&sp->lock, flags);

	index = buffer->next_index;
	event = &buffer->events[index];
	while (event->serial_number < reader->next_serial_number) {
		index = (index + 1) % IBMASM_NUM_EVENTS;
		event = &buffer->events[index];
	}
	memcpy(reader->data, event->data, event->data_size);
	reader->data_size = event->data_size;
	reader->next_serial_number = event->serial_number + 1;

	spin_unlock_irqrestore(&sp->lock, flags);

	return event->data_size;
}