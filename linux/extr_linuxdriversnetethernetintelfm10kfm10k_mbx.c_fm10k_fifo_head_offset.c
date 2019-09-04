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
typedef  int u16 ;
struct fm10k_mbx_fifo {int head; int size; } ;

/* Variables and functions */

__attribute__((used)) static u16 fm10k_fifo_head_offset(struct fm10k_mbx_fifo *fifo, u16 offset)
{
	return (fifo->head + offset) & (fifo->size - 1);
}