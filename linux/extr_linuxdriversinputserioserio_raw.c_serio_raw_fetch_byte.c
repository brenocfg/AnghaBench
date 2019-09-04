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
struct serio_raw {size_t head; size_t tail; char* queue; int /*<<< orphan*/  serio; } ;

/* Variables and functions */
 int SERIO_RAW_QUEUE_LEN ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool serio_raw_fetch_byte(struct serio_raw *serio_raw, char *c)
{
	bool empty;

	serio_pause_rx(serio_raw->serio);

	empty = serio_raw->head == serio_raw->tail;
	if (!empty) {
		*c = serio_raw->queue[serio_raw->tail];
		serio_raw->tail = (serio_raw->tail + 1) % SERIO_RAW_QUEUE_LEN;
	}

	serio_continue_rx(serio_raw->serio);

	return !empty;
}