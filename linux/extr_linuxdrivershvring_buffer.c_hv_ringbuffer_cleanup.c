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
struct hv_ring_buffer_info {int /*<<< orphan*/  ring_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

void hv_ringbuffer_cleanup(struct hv_ring_buffer_info *ring_info)
{
	vunmap(ring_info->ring_buffer);
}