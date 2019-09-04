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
 int /*<<< orphan*/  KEMPLD_MUTEX_KEY ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kempld_release_hardware_mutex(struct kempld_device_data *pld)
{
	/* The harware mutex is released when 1 is written to the mutex bit. */
	iowrite8(KEMPLD_MUTEX_KEY, pld->io_index);
}