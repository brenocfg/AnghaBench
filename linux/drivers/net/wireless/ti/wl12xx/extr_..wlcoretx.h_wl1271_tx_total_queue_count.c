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
struct wl1271 {scalar_t__* tx_queue_count; } ;

/* Variables and functions */
 int NUM_TX_QUEUES ; 

__attribute__((used)) static inline int wl1271_tx_total_queue_count(struct wl1271 *wl)
{
	int i, count = 0;

	for (i = 0; i < NUM_TX_QUEUES; i++)
		count += wl->tx_queue_count[i];

	return count;
}