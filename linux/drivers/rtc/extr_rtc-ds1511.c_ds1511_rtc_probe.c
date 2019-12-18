#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rtc_plat_data {scalar_t__ irq; TYPE_1__* rtc; int /*<<< orphan*/  lock; TYPE_1__* ioaddr; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct nvmem_config {char* name; int word_size; int stride; int /*<<< orphan*/ * priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int nvram_old_abi; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int DS1511_BLF1 ; 
 int /*<<< orphan*/  DS1511_BME ; 
 int /*<<< orphan*/  DS1511_RAM_MAX ; 
 int /*<<< orphan*/  DS1511_WD_MSEC ; 
 int /*<<< orphan*/  DS1511_WD_SEC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RTC_CMD ; 
 int /*<<< orphan*/  RTC_CMD1 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct rtc_plat_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 TYPE_1__* ds1511_base ; 
 int /*<<< orphan*/  ds1511_interrupt ; 
 int /*<<< orphan*/  ds1511_nvram_read ; 
 int /*<<< orphan*/  ds1511_nvram_write ; 
 int /*<<< orphan*/  ds1511_rtc_ops ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_plat_data*) ; 
 int /*<<< orphan*/  rtc_enable_update () ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int rtc_read (int /*<<< orphan*/ ) ; 
 int rtc_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  rtc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1511_rtc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct rtc_plat_data *pdata;
	int ret = 0;
	struct nvmem_config ds1511_nvmem_cfg = {
		.name = "ds1511_nvram",
		.word_size = 1,
		.stride = 1,
		.size = DS1511_RAM_MAX,
		.reg_read = ds1511_nvram_read,
		.reg_write = ds1511_nvram_write,
		.priv = &pdev->dev,
	};

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ds1511_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ds1511_base))
		return PTR_ERR(ds1511_base);
	pdata->ioaddr = ds1511_base;
	pdata->irq = platform_get_irq(pdev, 0);

	/*
	 * turn on the clock and the crystal, etc.
	 */
	rtc_write(DS1511_BME, RTC_CMD);
	rtc_write(0, RTC_CMD1);
	/*
	 * clear the wdog counter
	 */
	rtc_write(0, DS1511_WD_MSEC);
	rtc_write(0, DS1511_WD_SEC);
	/*
	 * start the clock
	 */
	rtc_enable_update();

	/*
	 * check for a dying bat-tree
	 */
	if (rtc_read(RTC_CMD1) & DS1511_BLF1)
		dev_warn(&pdev->dev, "voltage-low detected.\n");

	spin_lock_init(&pdata->lock);
	platform_set_drvdata(pdev, pdata);

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(pdata->rtc))
		return PTR_ERR(pdata->rtc);

	pdata->rtc->ops = &ds1511_rtc_ops;

	pdata->rtc->nvram_old_abi = true;

	ret = rtc_register_device(pdata->rtc);
	if (ret)
		return ret;

	rtc_nvmem_register(pdata->rtc, &ds1511_nvmem_cfg);

	/*
	 * if the platform has an interrupt in mind for this device,
	 * then by all means, set it
	 */
	if (pdata->irq > 0) {
		rtc_read(RTC_CMD1);
		if (devm_request_irq(&pdev->dev, pdata->irq, ds1511_interrupt,
			IRQF_SHARED, pdev->name, pdev) < 0) {

			dev_warn(&pdev->dev, "interrupt not available.\n");
			pdata->irq = 0;
		}
	}

	return 0;
}