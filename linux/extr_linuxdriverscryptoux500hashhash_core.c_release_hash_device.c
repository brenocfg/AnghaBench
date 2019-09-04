#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hash_device_data {int /*<<< orphan*/  ctx_lock; TYPE_1__* current_ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_allocation; } ;
struct TYPE_3__ {int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 TYPE_2__ driver_data ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_hash_device(struct hash_device_data *device_data)
{
	spin_lock(&device_data->ctx_lock);
	device_data->current_ctx->device = NULL;
	device_data->current_ctx = NULL;
	spin_unlock(&device_data->ctx_lock);

	/*
	 * The down_interruptible part for this semaphore is called in
	 * cryp_get_device_data.
	 */
	up(&driver_data.device_allocation);
}