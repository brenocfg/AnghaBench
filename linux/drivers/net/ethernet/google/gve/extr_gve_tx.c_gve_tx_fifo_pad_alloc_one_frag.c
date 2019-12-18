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
struct gve_tx_fifo {scalar_t__ head; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static int gve_tx_fifo_pad_alloc_one_frag(struct gve_tx_fifo *fifo,
					  size_t bytes)
{
	return (fifo->head + bytes < fifo->size) ? 0 : fifo->size - fifo->head;
}