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
struct ec_event_queue {size_t head; size_t tail; scalar_t__* entries; } ;

/* Variables and functions */

__attribute__((used)) static inline bool event_queue_full(struct ec_event_queue *q)
{
	/* head==tail when both full and empty, but head!=NULL when full */
	return q->head == q->tail && q->entries[q->head];
}