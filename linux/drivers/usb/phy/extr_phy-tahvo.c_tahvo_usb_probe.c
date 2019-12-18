#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* otg; int /*<<< orphan*/  set_suspend; int /*<<< orphan*/  label; TYPE_4__* dev; } ;
struct tahvo_usb {scalar_t__ tahvo_mode; int vbus_state; int /*<<< orphan*/  ick; TYPE_2__ phy; int /*<<< orphan*/  irq; int /*<<< orphan*/  extcon; int /*<<< orphan*/  serialize; struct platform_device* pt_dev; } ;
struct retu_dev {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  set_peripheral; int /*<<< orphan*/  set_host; TYPE_2__* usb_phy; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TAHVO_MODE_HOST ; 
 scalar_t__ TAHVO_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  TAHVO_REG_IDSR ; 
 int TAHVO_STAT_VBUS ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct retu_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct tahvo_usb*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tahvo_usb*) ; 
 int retu_read (struct retu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tahvo_cable ; 
 int /*<<< orphan*/  tahvo_usb_power_off (struct tahvo_usb*) ; 
 int /*<<< orphan*/  tahvo_usb_set_host ; 
 int /*<<< orphan*/  tahvo_usb_set_peripheral ; 
 int /*<<< orphan*/  tahvo_usb_set_suspend ; 
 int /*<<< orphan*/  tahvo_usb_vbus_interrupt ; 
 int usb_add_phy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_phy (TYPE_2__*) ; 

__attribute__((used)) static int tahvo_usb_probe(struct platform_device *pdev)
{
	struct retu_dev *rdev = dev_get_drvdata(pdev->dev.parent);
	struct tahvo_usb *tu;
	int ret;

	tu = devm_kzalloc(&pdev->dev, sizeof(*tu), GFP_KERNEL);
	if (!tu)
		return -ENOMEM;

	tu->phy.otg = devm_kzalloc(&pdev->dev, sizeof(*tu->phy.otg),
				   GFP_KERNEL);
	if (!tu->phy.otg)
		return -ENOMEM;

	tu->pt_dev = pdev;

	/* Default mode */
#ifdef CONFIG_TAHVO_USB_HOST_BY_DEFAULT
	tu->tahvo_mode = TAHVO_MODE_HOST;
#else
	tu->tahvo_mode = TAHVO_MODE_PERIPHERAL;
#endif

	mutex_init(&tu->serialize);

	tu->ick = devm_clk_get(&pdev->dev, "usb_l4_ick");
	if (!IS_ERR(tu->ick))
		clk_enable(tu->ick);

	/*
	 * Set initial state, so that we generate kevents only on state changes.
	 */
	tu->vbus_state = retu_read(rdev, TAHVO_REG_IDSR) & TAHVO_STAT_VBUS;

	tu->extcon = devm_extcon_dev_allocate(&pdev->dev, tahvo_cable);
	if (IS_ERR(tu->extcon)) {
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		ret = PTR_ERR(tu->extcon);
		goto err_disable_clk;
	}

	ret = devm_extcon_dev_register(&pdev->dev, tu->extcon);
	if (ret) {
		dev_err(&pdev->dev, "could not register extcon device: %d\n",
			ret);
		goto err_disable_clk;
	}

	/* Set the initial cable state. */
	extcon_set_state_sync(tu->extcon, EXTCON_USB_HOST,
			       tu->tahvo_mode == TAHVO_MODE_HOST);
	extcon_set_state_sync(tu->extcon, EXTCON_USB, tu->vbus_state);

	/* Create OTG interface */
	tahvo_usb_power_off(tu);
	tu->phy.dev = &pdev->dev;
	tu->phy.otg->state = OTG_STATE_UNDEFINED;
	tu->phy.label = DRIVER_NAME;
	tu->phy.set_suspend = tahvo_usb_set_suspend;

	tu->phy.otg->usb_phy = &tu->phy;
	tu->phy.otg->set_host = tahvo_usb_set_host;
	tu->phy.otg->set_peripheral = tahvo_usb_set_peripheral;

	ret = usb_add_phy(&tu->phy, USB_PHY_TYPE_USB2);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot register USB transceiver: %d\n",
			ret);
		goto err_disable_clk;
	}

	dev_set_drvdata(&pdev->dev, tu);

	tu->irq = platform_get_irq(pdev, 0);
	ret = request_threaded_irq(tu->irq, NULL, tahvo_usb_vbus_interrupt,
				   IRQF_ONESHOT,
				   "tahvo-vbus", tu);
	if (ret) {
		dev_err(&pdev->dev, "could not register tahvo-vbus irq: %d\n",
			ret);
		goto err_remove_phy;
	}

	return 0;

err_remove_phy:
	usb_remove_phy(&tu->phy);
err_disable_clk:
	if (!IS_ERR(tu->ick))
		clk_disable(tu->ick);

	return ret;
}