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
struct zynq_gpio {TYPE_1__* p_data; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int ZYNQ_GPIO_QUIRK_IS_ZYNQ ; 

__attribute__((used)) static int zynq_gpio_is_zynq(struct zynq_gpio *gpio)
{
	return !!(gpio->p_data->quirks & ZYNQ_GPIO_QUIRK_IS_ZYNQ);
}