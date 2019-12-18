#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct tegra_xusb_port {TYPE_1__ dev; } ;
struct tegra_xusb_usb2_port {int mode; int /*<<< orphan*/  supply; int /*<<< orphan*/  internal; struct tegra_xusb_port base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int USB_DR_MODE_HOST ; 
 int USB_DR_MODE_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  modes ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 

__attribute__((used)) static int tegra_xusb_usb2_port_parse_dt(struct tegra_xusb_usb2_port *usb2)
{
	struct tegra_xusb_port *port = &usb2->base;
	struct device_node *np = port->dev.of_node;
	const char *mode;

	usb2->internal = of_property_read_bool(np, "nvidia,internal");

	if (!of_property_read_string(np, "mode", &mode)) {
		int err = match_string(modes, ARRAY_SIZE(modes), mode);
		if (err < 0) {
			dev_err(&port->dev, "invalid value %s for \"mode\"\n",
				mode);
			usb2->mode = USB_DR_MODE_UNKNOWN;
		} else {
			usb2->mode = err;
		}
	} else {
		usb2->mode = USB_DR_MODE_HOST;
	}

	usb2->supply = devm_regulator_get(&port->dev, "vbus");
	return PTR_ERR_OR_ZERO(usb2->supply);
}