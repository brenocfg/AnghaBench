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
struct dma_fifo {int size; int avail; } ;

/* Variables and functions */

__attribute__((used)) static inline int dma_fifo_level(struct dma_fifo *fifo)
{
	return fifo->size - fifo->avail;
}