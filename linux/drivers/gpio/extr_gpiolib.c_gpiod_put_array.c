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
struct gpio_descs {unsigned int ndescs; int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gpio_descs*) ; 

void gpiod_put_array(struct gpio_descs *descs)
{
	unsigned int i;

	for (i = 0; i < descs->ndescs; i++)
		gpiod_put(descs->desc[i]);

	kfree(descs);
}