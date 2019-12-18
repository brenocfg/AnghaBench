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
 int MAX_OCTEON_DEVICES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oct_set_config_info (int,int) ; 
 int /*<<< orphan*/  octeon_device ; 
 int /*<<< orphan*/  octeon_devices_lock ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void octeon_init_device_list(int conf_type)
{
	int i;

	memset(octeon_device, 0, (sizeof(void *) * MAX_OCTEON_DEVICES));
	for (i = 0; i <  MAX_OCTEON_DEVICES; i++)
		oct_set_config_info(i, conf_type);
	spin_lock_init(&octeon_devices_lock);
}