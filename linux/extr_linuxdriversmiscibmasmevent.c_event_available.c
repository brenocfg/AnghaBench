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
struct event_reader {scalar_t__ next_serial_number; } ;
struct event_buffer {scalar_t__ next_serial_number; } ;

/* Variables and functions */

__attribute__((used)) static inline int event_available(struct event_buffer *b, struct event_reader *r)
{
	return (r->next_serial_number < b->next_serial_number);
}