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
struct megasas_instance {unsigned int drv_buf_alloc; scalar_t__ fw_crash_buffer_size; int /*<<< orphan*/  fw_crash_state; scalar_t__ drv_buf_index; scalar_t__* crash_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNAVAILABLE ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 

void
megasas_free_host_crash_buffer(struct megasas_instance *instance)
{
	unsigned int i;
	for (i = 0; i < instance->drv_buf_alloc; i++) {
		if (instance->crash_buf[i])
			vfree(instance->crash_buf[i]);
	}
	instance->drv_buf_index = 0;
	instance->drv_buf_alloc = 0;
	instance->fw_crash_state = UNAVAILABLE;
	instance->fw_crash_buffer_size = 0;
}