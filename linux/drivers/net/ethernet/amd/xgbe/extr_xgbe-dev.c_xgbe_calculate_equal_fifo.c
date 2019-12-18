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

/* Variables and functions */
 unsigned int XGMAC_FIFO_UNIT ; 

__attribute__((used)) static void xgbe_calculate_equal_fifo(unsigned int fifo_size,
				      unsigned int queue_count,
				      unsigned int *fifo)
{
	unsigned int q_fifo_size;
	unsigned int p_fifo;
	unsigned int i;

	q_fifo_size = fifo_size / queue_count;

	/* Calculate the fifo setting by dividing the queue's fifo size
	 * by the fifo allocation increment (with 0 representing the
	 * base allocation increment so decrement the result by 1).
	 */
	p_fifo = q_fifo_size / XGMAC_FIFO_UNIT;
	if (p_fifo)
		p_fifo--;

	/* Distribute the fifo equally amongst the queues */
	for (i = 0; i < queue_count; i++)
		fifo[i] = p_fifo;
}