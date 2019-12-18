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
struct ibmasm_event {unsigned int data_size; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  data; } ;
struct event_buffer {size_t next_index; int /*<<< orphan*/  next_serial_number; struct ibmasm_event* events; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMASM_EVENT_MAX_SIZE ; 
 int IBMASM_NUM_EVENTS ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,void*,unsigned int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_event_readers (struct service_processor*) ; 

void ibmasm_receive_event(struct service_processor *sp, void *data, unsigned int data_size)
{
	struct event_buffer *buffer = sp->event_buffer;
	struct ibmasm_event *event;
	unsigned long flags;

	data_size = min(data_size, IBMASM_EVENT_MAX_SIZE);

	spin_lock_irqsave(&sp->lock, flags);
	/* copy the event into the next slot in the circular buffer */
	event = &buffer->events[buffer->next_index];
	memcpy_fromio(event->data, data, data_size);
	event->data_size = data_size;
	event->serial_number = buffer->next_serial_number;

	/* advance indices in the buffer */
	buffer->next_index = (buffer->next_index + 1) % IBMASM_NUM_EVENTS;
	buffer->next_serial_number++;
	spin_unlock_irqrestore(&sp->lock, flags);

	wake_up_event_readers(sp);
}