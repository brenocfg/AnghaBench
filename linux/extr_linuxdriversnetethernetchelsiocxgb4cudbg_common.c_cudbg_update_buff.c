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
struct cudbg_buffer {scalar_t__ size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */

void cudbg_update_buff(struct cudbg_buffer *pin_buff,
		       struct cudbg_buffer *pout_buff)
{
	/* We already write to buffer provided by ethool, so just
	 * increment offset to next free space.
	 */
	pout_buff->offset += pin_buff->size;
}