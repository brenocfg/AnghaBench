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
struct gve_tx_fifo {int /*<<< orphan*/  available; } ;

/* Variables and functions */
 size_t atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gve_tx_fifo_can_alloc(struct gve_tx_fifo *fifo, size_t bytes)
{
	return (atomic_read(&fifo->available) <= bytes) ? false : true;
}