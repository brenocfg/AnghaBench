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

/* Variables and functions */
 int S3C_CAMIF_NUM_GPIOS ; 
 int /*<<< orphan*/  camif_get_gpios (int*,int*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 

void s3c_camif_gpio_put(void)
{
	int i, gpio_start, gpio_reset;

	camif_get_gpios(&gpio_start, &gpio_reset);

	for (i = 0; i < S3C_CAMIF_NUM_GPIOS; i++) {
		int gpio = gpio_start + i;
		if (gpio != gpio_reset)
			gpio_free(gpio);
	}
}