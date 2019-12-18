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
 int /*<<< orphan*/ * op_ring_buffer ; 
 int /*<<< orphan*/  ring_buffer_free (int /*<<< orphan*/ *) ; 

void free_cpu_buffers(void)
{
	if (op_ring_buffer)
		ring_buffer_free(op_ring_buffer);
	op_ring_buffer = NULL;
}