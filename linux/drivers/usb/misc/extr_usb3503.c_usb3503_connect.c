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
struct usb3503 {int port_off_mask; int /*<<< orphan*/  mode; int /*<<< orphan*/  gpio_connect; scalar_t__ regmap; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3503_CFG1 ; 
 int /*<<< orphan*/  USB3503_MODE_HUB ; 
 int /*<<< orphan*/  USB3503_PDS ; 
 int USB3503_SELF_BUS_PWR ; 
 int USB3503_SPILOCK_CONFIG ; 
 int USB3503_SPILOCK_CONNECT ; 
 int /*<<< orphan*/  USB3503_SP_ILOCK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb3503_reset (struct usb3503*,int) ; 

__attribute__((used)) static int usb3503_connect(struct usb3503 *hub)
{
	struct device *dev = hub->dev;
	int err;

	usb3503_reset(hub, 1);

	if (hub->regmap) {
		/* SP_ILOCK: set connect_n, config_n for config */
		err = regmap_write(hub->regmap, USB3503_SP_ILOCK,
			   (USB3503_SPILOCK_CONNECT
				 | USB3503_SPILOCK_CONFIG));
		if (err < 0) {
			dev_err(dev, "SP_ILOCK failed (%d)\n", err);
			return err;
		}

		/* PDS : Set the ports which are disabled in self-powered mode. */
		if (hub->port_off_mask) {
			err = regmap_update_bits(hub->regmap, USB3503_PDS,
					hub->port_off_mask,
					hub->port_off_mask);
			if (err < 0) {
				dev_err(dev, "PDS failed (%d)\n", err);
				return err;
			}
		}

		/* CFG1 : Set SELF_BUS_PWR, this enables self-powered operation. */
		err = regmap_update_bits(hub->regmap, USB3503_CFG1,
					 USB3503_SELF_BUS_PWR,
					 USB3503_SELF_BUS_PWR);
		if (err < 0) {
			dev_err(dev, "CFG1 failed (%d)\n", err);
			return err;
		}

		/* SP_LOCK: clear connect_n, config_n for hub connect */
		err = regmap_update_bits(hub->regmap, USB3503_SP_ILOCK,
					 (USB3503_SPILOCK_CONNECT
					  | USB3503_SPILOCK_CONFIG), 0);
		if (err < 0) {
			dev_err(dev, "SP_ILOCK failed (%d)\n", err);
			return err;
		}
	}

	if (gpio_is_valid(hub->gpio_connect))
		gpio_set_value_cansleep(hub->gpio_connect, 1);

	hub->mode = USB3503_MODE_HUB;
	dev_info(dev, "switched to HUB mode\n");

	return 0;
}