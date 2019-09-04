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
struct service_processor {int /*<<< orphan*/  lock; TYPE_1__* event_buffer; } ;
struct event_reader {int /*<<< orphan*/  node; int /*<<< orphan*/  wait; int /*<<< orphan*/  next_serial_number; } ;
struct TYPE_2__ {int /*<<< orphan*/  readers; int /*<<< orphan*/  next_serial_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ibmasm_event_reader_register(struct service_processor *sp, struct event_reader *reader)
{
	unsigned long flags;

	reader->next_serial_number = sp->event_buffer->next_serial_number;
	init_waitqueue_head(&reader->wait);
	spin_lock_irqsave(&sp->lock, flags);
	list_add(&reader->node, &sp->event_buffer->readers);
	spin_unlock_irqrestore(&sp->lock, flags);
}