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
struct pi433_device {int /*<<< orphan*/ * gpiod; int /*<<< orphan*/ * irq_num; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NUM_DIO ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pi433_device*) ; 
 int /*<<< orphan*/  gpiod_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_gpio(struct pi433_device *device)
{
	int i;

	for (i = 0; i < NUM_DIO; i++) {
		/* check if gpiod is valid */
		if (IS_ERR(device->gpiod[i]))
			continue;

		free_irq(device->irq_num[i], device);
		gpiod_put(device->gpiod[i]);
	}
}