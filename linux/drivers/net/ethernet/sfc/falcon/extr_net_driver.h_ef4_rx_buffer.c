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
struct ef4_rx_queue {struct ef4_rx_buffer* buffer; } ;
struct ef4_rx_buffer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ef4_rx_buffer *ef4_rx_buffer(struct ef4_rx_queue *rx_queue,
						  unsigned int index)
{
	return &rx_queue->buffer[index];
}