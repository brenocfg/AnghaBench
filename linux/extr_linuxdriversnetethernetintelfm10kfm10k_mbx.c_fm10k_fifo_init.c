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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_mbx_fifo {scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */

__attribute__((used)) static void fm10k_fifo_init(struct fm10k_mbx_fifo *fifo, u32 *buffer, u16 size)
{
	fifo->buffer = buffer;
	fifo->size = size;
	fifo->head = 0;
	fifo->tail = 0;
}