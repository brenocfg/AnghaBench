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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  stdma_try_lock (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stdma_wait ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void stdma_lock(irq_handler_t handler, void *data)
{
	/* Since the DMA is used for file system purposes, we
	 have to sleep uninterruptible (there may be locked
	 buffers) */
	wait_event(stdma_wait, stdma_try_lock(handler, data));
}