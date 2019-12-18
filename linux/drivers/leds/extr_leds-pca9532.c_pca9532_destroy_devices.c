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
struct TYPE_4__ {scalar_t__ parent; } ;
struct pca9532_data {TYPE_2__ gpio; int /*<<< orphan*/ * idev; int /*<<< orphan*/  work; TYPE_1__* leds; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  ldev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PCA9532_TYPE_GPIO 131 
#define  PCA9532_TYPE_LED 130 
#define  PCA9532_TYPE_N2100_BEEP 129 
#define  PCA9532_TYPE_NONE 128 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca9532_destroy_devices(struct pca9532_data *data, int n_devs)
{
	int i = n_devs;

	if (!data)
		return -EINVAL;

	while (--i >= 0) {
		switch (data->leds[i].type) {
		case PCA9532_TYPE_NONE:
		case PCA9532_TYPE_GPIO:
			break;
		case PCA9532_TYPE_LED:
			led_classdev_unregister(&data->leds[i].ldev);
			break;
		case PCA9532_TYPE_N2100_BEEP:
			if (data->idev != NULL) {
				cancel_work_sync(&data->work);
				data->idev = NULL;
			}
			break;
		}
	}

#ifdef CONFIG_LEDS_PCA9532_GPIO
	if (data->gpio.parent)
		gpiochip_remove(&data->gpio);
#endif

	return 0;
}