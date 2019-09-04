#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_5__ {scalar_t__ base; int gpios; } ;
struct TYPE_4__ {int ngpio; struct device* parent; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,scalar_t__*) ; 
 int hweight_long (int) ; 
 TYPE_2__ params ; 
 TYPE_1__ winbond_gpio_chip ; 
 int winbond_gpio_configure (scalar_t__) ; 
 int winbond_sio_enter (scalar_t__) ; 
 int /*<<< orphan*/  winbond_sio_leave (scalar_t__) ; 

__attribute__((used)) static int winbond_gpio_iprobe(struct device *dev, unsigned int id)
{
	int ret;

	if (params.base == 0)
		return -EINVAL;

	ret = winbond_sio_enter(params.base);
	if (ret)
		return ret;

	ret = winbond_gpio_configure(params.base);

	winbond_sio_leave(params.base);

	if (ret)
		return ret;

	/*
	 * Add 8 gpios for every GPIO port that was enabled in gpios
	 * module parameter (that wasn't disabled earlier in
	 * winbond_gpio_configure() & co. due to, for example, a pin conflict).
	 */
	winbond_gpio_chip.ngpio = hweight_long(params.gpios) * 8;

	/*
	 * GPIO6 port has only 5 pins, so if it is enabled we have to adjust
	 * the total count appropriately
	 */
	if (params.gpios & BIT(5))
		winbond_gpio_chip.ngpio -= (8 - 5);

	winbond_gpio_chip.parent = dev;

	return devm_gpiochip_add_data(dev, &winbond_gpio_chip, &params.base);
}