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
struct bcma_hcd_device {int /*<<< orphan*/  gpio_desc; struct bcma_device* core; } ;
struct TYPE_4__ {int id; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct bcma_device {TYPE_1__ id; TYPE_2__ dev; } ;

/* Variables and functions */
#define  BCMA_CORE_NS_USB20 130 
#define  BCMA_CORE_NS_USB30 129 
#define  BCMA_CORE_USB20_HOST 128 
 int /*<<< orphan*/  CONFIG_ARM ; 
 int /*<<< orphan*/  CONFIG_MIPS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int bcma_hcd_usb20_init (struct bcma_hcd_device*) ; 
 int bcma_hcd_usb20_ns_init (struct bcma_hcd_device*) ; 
 int bcma_hcd_usb20_old_arm_init (struct bcma_hcd_device*) ; 
 int bcma_hcd_usb30_init (struct bcma_hcd_device*) ; 
 int /*<<< orphan*/  bcma_set_drvdata (struct bcma_device*,struct bcma_hcd_device*) ; 
 int /*<<< orphan*/  devm_gpiod_get (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct bcma_hcd_device* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcma_hcd_probe(struct bcma_device *core)
{
	int err;
	struct bcma_hcd_device *usb_dev;

	/* TODO: Probably need checks here; is the core connected? */

	usb_dev = devm_kzalloc(&core->dev, sizeof(struct bcma_hcd_device),
			       GFP_KERNEL);
	if (!usb_dev)
		return -ENOMEM;
	usb_dev->core = core;

	if (core->dev.of_node)
		usb_dev->gpio_desc = devm_gpiod_get(&core->dev, "vcc",
						    GPIOD_OUT_HIGH);

	switch (core->id.id) {
	case BCMA_CORE_USB20_HOST:
		if (IS_ENABLED(CONFIG_ARM))
			err = bcma_hcd_usb20_old_arm_init(usb_dev);
		else if (IS_ENABLED(CONFIG_MIPS))
			err = bcma_hcd_usb20_init(usb_dev);
		else
			err = -ENOTSUPP;
		break;
	case BCMA_CORE_NS_USB20:
		err = bcma_hcd_usb20_ns_init(usb_dev);
		break;
	case BCMA_CORE_NS_USB30:
		err = bcma_hcd_usb30_init(usb_dev);
		break;
	default:
		return -ENODEV;
	}
	if (err)
		return err;

	bcma_set_drvdata(core, usb_dev);
	return 0;
}