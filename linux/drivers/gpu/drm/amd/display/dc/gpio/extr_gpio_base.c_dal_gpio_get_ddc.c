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
struct hw_ddc {int dummy; } ;
struct TYPE_2__ {struct hw_ddc* ddc; } ;
struct gpio {TYPE_1__ hw_container; } ;

/* Variables and functions */

struct hw_ddc *dal_gpio_get_ddc(struct gpio *gpio)
{
	return gpio->hw_container.ddc;
}