#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct plat_vlynq_data* platform_data; } ;
struct vlynq_device {TYPE_1__ dev; } ;
struct plat_vlynq_data {int /*<<< orphan*/  reset_bit; int /*<<< orphan*/  gpio_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar7_device_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar7_gpio_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlynq_off(struct vlynq_device *dev)
{
	struct plat_vlynq_data *pdata = dev->dev.platform_data;

	ar7_gpio_disable(pdata->gpio_bit);
	gpio_free(pdata->gpio_bit);
	ar7_device_disable(pdata->reset_bit);
}