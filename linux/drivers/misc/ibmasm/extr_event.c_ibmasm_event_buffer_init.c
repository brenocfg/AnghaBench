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
struct service_processor {struct event_buffer* event_buffer; } ;
struct ibmasm_event {scalar_t__ serial_number; } ;
struct event_buffer {int next_serial_number; int /*<<< orphan*/  readers; struct ibmasm_event* events; scalar_t__ next_index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IBMASM_NUM_EVENTS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct event_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 

int ibmasm_event_buffer_init(struct service_processor *sp)
{
	struct event_buffer *buffer;
	struct ibmasm_event *event;
	int i;

	buffer = kmalloc(sizeof(struct event_buffer), GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	buffer->next_index = 0;
	buffer->next_serial_number = 1;

	event = buffer->events;
	for (i=0; i<IBMASM_NUM_EVENTS; i++, event++)
		event->serial_number = 0;

	INIT_LIST_HEAD(&buffer->readers);

	sp->event_buffer = buffer;

	return 0;
}