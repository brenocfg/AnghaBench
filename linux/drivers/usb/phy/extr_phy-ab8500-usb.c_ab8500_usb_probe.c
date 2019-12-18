#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {int /*<<< orphan*/  set_peripheral; int /*<<< orphan*/  set_host; TYPE_1__* usb_phy; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {char* label; struct usb_otg* otg; int /*<<< orphan*/  set_suspend; TYPE_2__* dev; } ;
struct ab8500_usb {int flags; struct ab8500* ab8500; TYPE_1__ phy; int /*<<< orphan*/  sysclk; TYPE_2__* dev; int /*<<< orphan*/  phy_dis_work; } ;
struct ab8500 {int dummy; } ;

/* Variables and functions */
 int AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE ; 
 int AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ ; 
 int AB8500_USB_FLAG_USE_LINK_STATUS_IRQ ; 
 int AB8500_USB_FLAG_USE_VBUS_DET_IRQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int ab8500_usb_irq_setup (struct platform_device*,struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_phy_disable_work ; 
 int ab8500_usb_regulator_get (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_restart_phy (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_set_ab8500_tuning_values (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_set_ab8505_tuning_values (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_set_host ; 
 int /*<<< orphan*/  ab8500_usb_set_peripheral ; 
 int /*<<< orphan*/  ab8500_usb_set_suspend ; 
 int /*<<< orphan*/  ab8500_usb_wd_workaround (struct ab8500_usb*) ; 
 int abx500_get_chip_id (TYPE_2__*) ; 
 int /*<<< orphan*/  abx500_usb_link_status_update (struct ab8500_usb*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct ab8500* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ab8500 (struct ab8500*) ; 
 scalar_t__ is_ab8500_1p1_or_earlier (struct ab8500*) ; 
 scalar_t__ is_ab8500_2p0_or_earlier (struct ab8500*) ; 
 scalar_t__ is_ab8505 (struct ab8500*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ab8500_usb*) ; 
 int usb_add_phy (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_usb_probe(struct platform_device *pdev)
{
	struct ab8500_usb	*ab;
	struct ab8500		*ab8500;
	struct usb_otg		*otg;
	int err;
	int rev;

	ab8500 = dev_get_drvdata(pdev->dev.parent);
	rev = abx500_get_chip_id(&pdev->dev);

	if (is_ab8500_1p1_or_earlier(ab8500)) {
		dev_err(&pdev->dev, "Unsupported AB8500 chip rev=%d\n", rev);
		return -ENODEV;
	}

	ab = devm_kzalloc(&pdev->dev, sizeof(*ab), GFP_KERNEL);
	if (!ab)
		return -ENOMEM;

	otg = devm_kzalloc(&pdev->dev, sizeof(*otg), GFP_KERNEL);
	if (!otg)
		return -ENOMEM;

	ab->dev			= &pdev->dev;
	ab->ab8500		= ab8500;
	ab->phy.dev		= ab->dev;
	ab->phy.otg		= otg;
	ab->phy.label		= "ab8500";
	ab->phy.set_suspend	= ab8500_usb_set_suspend;
	ab->phy.otg->state	= OTG_STATE_UNDEFINED;

	otg->usb_phy		= &ab->phy;
	otg->set_host		= ab8500_usb_set_host;
	otg->set_peripheral	= ab8500_usb_set_peripheral;

	if (is_ab8500(ab->ab8500)) {
		ab->flags |= AB8500_USB_FLAG_USE_LINK_STATUS_IRQ |
			AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ |
			AB8500_USB_FLAG_USE_VBUS_DET_IRQ |
			AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE;
	} else if (is_ab8505(ab->ab8500)) {
		ab->flags |= AB8500_USB_FLAG_USE_LINK_STATUS_IRQ |
			AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ |
			AB8500_USB_FLAG_USE_VBUS_DET_IRQ |
			AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE;
	}

	/* Disable regulator voltage setting for AB8500 <= v2.0 */
	if (is_ab8500_2p0_or_earlier(ab->ab8500))
		ab->flags &= ~AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE;

	platform_set_drvdata(pdev, ab);

	/* all: Disable phy when called from set_host and set_peripheral */
	INIT_WORK(&ab->phy_dis_work, ab8500_usb_phy_disable_work);

	err = ab8500_usb_regulator_get(ab);
	if (err)
		return err;

	ab->sysclk = devm_clk_get(ab->dev, "sysclk");
	if (IS_ERR(ab->sysclk)) {
		dev_err(ab->dev, "Could not get sysclk.\n");
		return PTR_ERR(ab->sysclk);
	}

	err = ab8500_usb_irq_setup(pdev, ab);
	if (err < 0)
		return err;

	err = usb_add_phy(&ab->phy, USB_PHY_TYPE_USB2);
	if (err) {
		dev_err(&pdev->dev, "Can't register transceiver\n");
		return err;
	}

	if (is_ab8500(ab->ab8500) && !is_ab8500_2p0_or_earlier(ab->ab8500))
		/* Phy tuning values for AB8500 > v2.0 */
		ab8500_usb_set_ab8500_tuning_values(ab);
	else if (is_ab8505(ab->ab8500))
		/* Phy tuning values for AB8505 */
		ab8500_usb_set_ab8505_tuning_values(ab);

	/* Needed to enable ID detection. */
	ab8500_usb_wd_workaround(ab);

	/*
	 * This is required for usb-link-status to work properly when a
	 * cable is connected at boot time.
	 */
	ab8500_usb_restart_phy(ab);

	abx500_usb_link_status_update(ab);

	dev_info(&pdev->dev, "revision 0x%2x driver initialized\n", rev);

	return 0;
}