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
struct TYPE_2__ {int /*<<< orphan*/  keybd_dev; int /*<<< orphan*/  mouse_dev; } ;
struct service_processor {TYPE_1__ remote; } ;
struct remote_input {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ INPUT_TYPE_KEYBOARD ; 
 scalar_t__ INPUT_TYPE_MOUSE ; 
 unsigned long advance_queue_reader (struct service_processor*,unsigned long) ; 
 int /*<<< orphan*/  get_queue_entry (struct service_processor*,unsigned long) ; 
 unsigned long get_queue_reader (struct service_processor*) ; 
 unsigned long get_queue_writer (struct service_processor*) ; 
 int /*<<< orphan*/  memcpy_fromio (struct remote_input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_input (struct remote_input*) ; 
 int /*<<< orphan*/  send_keyboard_event (int /*<<< orphan*/ ,struct remote_input*) ; 
 int /*<<< orphan*/  send_mouse_event (int /*<<< orphan*/ ,struct remote_input*) ; 

void ibmasm_handle_mouse_interrupt(struct service_processor *sp)
{
	unsigned long reader;
	unsigned long writer;
	struct remote_input input;

	reader = get_queue_reader(sp);
	writer = get_queue_writer(sp);

	while (reader != writer) {
		memcpy_fromio(&input, get_queue_entry(sp, reader),
				sizeof(struct remote_input));

		print_input(&input);
		if (input.type == INPUT_TYPE_MOUSE) {
			send_mouse_event(sp->remote.mouse_dev, &input);
		} else if (input.type == INPUT_TYPE_KEYBOARD) {
			send_keyboard_event(sp->remote.keybd_dev, &input);
		} else
			break;

		reader = advance_queue_reader(sp, reader);
		writer = get_queue_writer(sp);
	}
}