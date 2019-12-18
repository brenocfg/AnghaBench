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
struct mdio_device {scalar_t__ reset_gpio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int PTR_ERR_OR_ZERO (scalar_t__) ; 
 scalar_t__ gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (scalar_t__,char*) ; 

__attribute__((used)) static int mdiobus_register_gpiod(struct mdio_device *mdiodev)
{
	int error;

	/* Deassert the optional reset signal */
	mdiodev->reset_gpio = gpiod_get_optional(&mdiodev->dev,
						 "reset", GPIOD_OUT_LOW);
	error = PTR_ERR_OR_ZERO(mdiodev->reset_gpio);
	if (error)
		return error;

	if (mdiodev->reset_gpio)
		gpiod_set_consumer_name(mdiodev->reset_gpio, "PHY reset");

	return 0;
}