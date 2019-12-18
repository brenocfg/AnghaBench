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
struct timer_list {int dummy; } ;
struct ef4_rx_queue {int /*<<< orphan*/  slow_fill_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_nic_generate_fill_event (struct ef4_rx_queue*) ; 
 struct ef4_rx_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ef4_rx_queue* rx_queue ; 
 int /*<<< orphan*/  slow_fill ; 

void ef4_rx_slow_fill(struct timer_list *t)
{
	struct ef4_rx_queue *rx_queue = from_timer(rx_queue, t, slow_fill);

	/* Post an event to cause NAPI to run and refill the queue */
	ef4_nic_generate_fill_event(rx_queue);
	++rx_queue->slow_fill_count;
}