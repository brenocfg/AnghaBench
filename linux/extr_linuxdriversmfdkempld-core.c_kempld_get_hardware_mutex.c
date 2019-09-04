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
struct kempld_device_data {int /*<<< orphan*/  io_index; } ;

/* Variables and functions */
 int KEMPLD_MUTEX_KEY ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void kempld_get_hardware_mutex(struct kempld_device_data *pld)
{
	/* The mutex bit will read 1 until access has been granted */
	while (ioread8(pld->io_index) & KEMPLD_MUTEX_KEY)
		usleep_range(1000, 3000);
}