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
struct kempld_platform_data {int /*<<< orphan*/  (* get_hardware_mutex ) (struct kempld_device_data*) ;} ;
struct kempld_device_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct kempld_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kempld_device_data*) ; 

void kempld_get_mutex(struct kempld_device_data *pld)
{
	const struct kempld_platform_data *pdata = dev_get_platdata(pld->dev);

	mutex_lock(&pld->lock);
	pdata->get_hardware_mutex(pld);
}