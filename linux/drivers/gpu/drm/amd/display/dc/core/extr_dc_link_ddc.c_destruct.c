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
struct ddc_service {scalar_t__ ddc_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_gpio_destroy_ddc (scalar_t__*) ; 

__attribute__((used)) static void destruct(struct ddc_service *ddc)
{
	if (ddc->ddc_pin)
		dal_gpio_destroy_ddc(&ddc->ddc_pin);
}