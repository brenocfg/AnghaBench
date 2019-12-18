#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct power_supply_config {int /*<<< orphan*/  attr_grp; struct pcf50633_mbc* drv_data; int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pcf50633_mbc {TYPE_3__* pcf; void* ac; void* usb; void* adapter; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_batteries; int /*<<< orphan*/  batteries; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PCF50633_IRQ_ADPINS ; 
 int /*<<< orphan*/  PCF50633_IRQ_USBINS ; 
 int PCF50633_MBCS1_ADAPTPRES ; 
 int PCF50633_MBCS1_USBPRES ; 
 int /*<<< orphan*/  PCF50633_REG_MBCS1 ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* dev_to_pcf50633 (int /*<<< orphan*/ ) ; 
 struct pcf50633_mbc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mbc_irq_handlers ; 
 int /*<<< orphan*/  pcf50633_mbc_ac_desc ; 
 int /*<<< orphan*/  pcf50633_mbc_adapter_desc ; 
 int /*<<< orphan*/  pcf50633_mbc_irq_handler (int /*<<< orphan*/ ,struct pcf50633_mbc*) ; 
 int /*<<< orphan*/  pcf50633_mbc_sysfs_groups ; 
 int /*<<< orphan*/  pcf50633_mbc_usb_desc ; 
 int pcf50633_reg_read (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf50633_register_irq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct pcf50633_mbc*),struct pcf50633_mbc*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pcf50633_mbc*) ; 
 void* power_supply_register (TYPE_2__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (void*) ; 

__attribute__((used)) static int pcf50633_mbc_probe(struct platform_device *pdev)
{
	struct power_supply_config psy_cfg = {};
	struct power_supply_config usb_psy_cfg;
	struct pcf50633_mbc *mbc;
	int i;
	u8 mbcs1;

	mbc = devm_kzalloc(&pdev->dev, sizeof(*mbc), GFP_KERNEL);
	if (!mbc)
		return -ENOMEM;

	platform_set_drvdata(pdev, mbc);
	mbc->pcf = dev_to_pcf50633(pdev->dev.parent);

	/* Set up IRQ handlers */
	for (i = 0; i < ARRAY_SIZE(mbc_irq_handlers); i++)
		pcf50633_register_irq(mbc->pcf, mbc_irq_handlers[i],
					pcf50633_mbc_irq_handler, mbc);

	psy_cfg.supplied_to		= mbc->pcf->pdata->batteries;
	psy_cfg.num_supplicants		= mbc->pcf->pdata->num_batteries;
	psy_cfg.drv_data		= mbc;

	/* Create power supplies */
	mbc->adapter = power_supply_register(&pdev->dev,
					     &pcf50633_mbc_adapter_desc,
					     &psy_cfg);
	if (IS_ERR(mbc->adapter)) {
		dev_err(mbc->pcf->dev, "failed to register adapter\n");
		return PTR_ERR(mbc->adapter);
	}

	usb_psy_cfg = psy_cfg;
	usb_psy_cfg.attr_grp = pcf50633_mbc_sysfs_groups;

	mbc->usb = power_supply_register(&pdev->dev, &pcf50633_mbc_usb_desc,
					 &usb_psy_cfg);
	if (IS_ERR(mbc->usb)) {
		dev_err(mbc->pcf->dev, "failed to register usb\n");
		power_supply_unregister(mbc->adapter);
		return PTR_ERR(mbc->usb);
	}

	mbc->ac = power_supply_register(&pdev->dev, &pcf50633_mbc_ac_desc,
					&psy_cfg);
	if (IS_ERR(mbc->ac)) {
		dev_err(mbc->pcf->dev, "failed to register ac\n");
		power_supply_unregister(mbc->adapter);
		power_supply_unregister(mbc->usb);
		return PTR_ERR(mbc->ac);
	}

	mbcs1 = pcf50633_reg_read(mbc->pcf, PCF50633_REG_MBCS1);
	if (mbcs1 & PCF50633_MBCS1_USBPRES)
		pcf50633_mbc_irq_handler(PCF50633_IRQ_USBINS, mbc);
	if (mbcs1 & PCF50633_MBCS1_ADAPTPRES)
		pcf50633_mbc_irq_handler(PCF50633_IRQ_ADPINS, mbc);

	return 0;
}