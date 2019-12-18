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
struct kempld_platform_data {int /*<<< orphan*/  (* release_hardware_mutex ) (struct kempld_device_data*) ;} ;
struct kempld_device_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct kempld_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kempld_device_data*) ; 

void kempld_release_mutex(struct kempld_device_data *pld)
{
	const struct kempld_platform_data *pdata = dev_get_platdata(pld->dev);

	pdata->release_hardware_mutex(pld);
	mutex_unlock(&pld->lock);
}