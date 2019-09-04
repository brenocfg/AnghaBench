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
struct tosa_bt_data {int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  gpio_pwr; } ;
struct rfkill {int dummy; } ;
struct TYPE_2__ {struct tosa_bt_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 struct rfkill* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_unregister (struct rfkill*) ; 
 int /*<<< orphan*/  tosa_bt_off (struct tosa_bt_data*) ; 

__attribute__((used)) static int tosa_bt_remove(struct platform_device *dev)
{
	struct tosa_bt_data *data = dev->dev.platform_data;
	struct rfkill *rfk = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);

	if (rfk) {
		rfkill_unregister(rfk);
		rfkill_destroy(rfk);
	}
	rfk = NULL;

	tosa_bt_off(data);

	gpio_free(data->gpio_pwr);
	gpio_free(data->gpio_reset);

	return 0;
}