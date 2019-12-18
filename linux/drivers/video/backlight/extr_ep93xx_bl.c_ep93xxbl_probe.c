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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct ep93xxbl {int /*<<< orphan*/  mmio; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EP93XX_DEF_BRIGHT ; 
 int /*<<< orphan*/  EP93XX_MAX_BRIGHT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ep93xxbl*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ep93xxbl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xxbl_ops ; 
 int /*<<< orphan*/  ep93xxbl_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ep93xxbl_probe(struct platform_device *dev)
{
	struct ep93xxbl *ep93xxbl;
	struct backlight_device *bl;
	struct backlight_properties props;
	struct resource *res;

	ep93xxbl = devm_kzalloc(&dev->dev, sizeof(*ep93xxbl), GFP_KERNEL);
	if (!ep93xxbl)
		return -ENOMEM;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENXIO;

	/*
	 * FIXME - We don't do a request_mem_region here because we are
	 * sharing the register space with the framebuffer driver (see
	 * drivers/video/ep93xx-fb.c) and doing so will cause the second
	 * loaded driver to return -EBUSY.
	 *
	 * NOTE: No locking is required; the framebuffer does not touch
	 * this register.
	 */
	ep93xxbl->mmio = devm_ioremap(&dev->dev, res->start,
				      resource_size(res));
	if (!ep93xxbl->mmio)
		return -ENXIO;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = EP93XX_MAX_BRIGHT;
	bl = devm_backlight_device_register(&dev->dev, dev->name, &dev->dev,
					ep93xxbl, &ep93xxbl_ops, &props);
	if (IS_ERR(bl))
		return PTR_ERR(bl);

	bl->props.brightness = EP93XX_DEF_BRIGHT;

	platform_set_drvdata(dev, bl);

	ep93xxbl_update_status(bl);

	return 0;
}