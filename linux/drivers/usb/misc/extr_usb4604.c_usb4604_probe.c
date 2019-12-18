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
typedef  int /*<<< orphan*/  u32 ;
struct usb4604 {int /*<<< orphan*/  mode; struct gpio_desc* gpio_reset; struct device* dev; } ;
struct gpio_desc {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  USB4604_MODE_HUB ; 
 struct gpio_desc* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int usb4604_switch_mode (struct usb4604*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb4604_probe(struct usb4604 *hub)
{
	struct device *dev = hub->dev;
	struct device_node *np = dev->of_node;
	struct gpio_desc *gpio;
	u32 mode = USB4604_MODE_HUB;

	gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);
	hub->gpio_reset = gpio;

	if (of_property_read_u32(np, "initial-mode", &hub->mode))
		hub->mode = mode;

	return usb4604_switch_mode(hub, hub->mode);
}