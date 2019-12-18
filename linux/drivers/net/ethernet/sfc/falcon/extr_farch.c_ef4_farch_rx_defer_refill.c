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
struct ef4_rx_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_CHANNEL_MAGIC_FILL (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_farch_magic_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_rx_queue_channel (struct ef4_rx_queue*) ; 

void ef4_farch_rx_defer_refill(struct ef4_rx_queue *rx_queue)
{
	ef4_farch_magic_event(ef4_rx_queue_channel(rx_queue),
			      EF4_CHANNEL_MAGIC_FILL(rx_queue));
}