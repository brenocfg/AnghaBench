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
struct input_polled_dev {struct gpio_keys_polled_dev* private; } ;
struct gpio_keys_polled_dev {int /*<<< orphan*/  dev; struct gpio_keys_platform_data* pdata; } ;
struct gpio_keys_platform_data {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_keys_polled_close(struct input_polled_dev *dev)
{
	struct gpio_keys_polled_dev *bdev = dev->private;
	const struct gpio_keys_platform_data *pdata = bdev->pdata;

	if (pdata->disable)
		pdata->disable(bdev->dev);
}