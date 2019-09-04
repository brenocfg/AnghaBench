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
struct nullb_device {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_free_dev (struct nullb_device*) ; 
 int /*<<< orphan*/  null_free_device_storage (struct nullb_device*,int) ; 
 struct nullb_device* to_nullb_device (struct config_item*) ; 

__attribute__((used)) static void nullb_device_release(struct config_item *item)
{
	struct nullb_device *dev = to_nullb_device(item);

	null_free_device_storage(dev, false);
	null_free_dev(dev);
}