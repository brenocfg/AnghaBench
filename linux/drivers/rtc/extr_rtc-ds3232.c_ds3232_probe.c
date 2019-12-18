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
struct regmap {int dummy; } ;
struct nvmem_config {char* name; int stride; int word_size; int /*<<< orphan*/  type; struct regmap* priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; } ;
struct ds3232 {int irq; int /*<<< orphan*/  rtc; struct device* dev; struct regmap* regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_SRAM_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVMEM_TYPE_BATTERY_BACKED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ds3232*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int /*<<< orphan*/ ) ; 
 struct ds3232* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,struct device*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (struct device*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ds3232_check_rtc_status (struct device*) ; 
 int /*<<< orphan*/  ds3232_hwmon_register (struct device*,char const*) ; 
 int /*<<< orphan*/  ds3232_irq ; 
 int /*<<< orphan*/  ds3232_nvmem_read ; 
 int /*<<< orphan*/  ds3232_nvmem_write ; 
 int /*<<< orphan*/  ds3232_rtc_ops ; 
 int rtc_nvmem_register (int /*<<< orphan*/ ,struct nvmem_config*) ; 

__attribute__((used)) static int ds3232_probe(struct device *dev, struct regmap *regmap, int irq,
			const char *name)
{
	struct ds3232 *ds3232;
	int ret;
	struct nvmem_config nvmem_cfg = {
		.name = "ds3232_sram",
		.stride = 1,
		.size = DS3232_REG_SRAM_SIZE,
		.word_size = 1,
		.reg_read = ds3232_nvmem_read,
		.reg_write = ds3232_nvmem_write,
		.priv = regmap,
		.type = NVMEM_TYPE_BATTERY_BACKED
	};

	ds3232 = devm_kzalloc(dev, sizeof(*ds3232), GFP_KERNEL);
	if (!ds3232)
		return -ENOMEM;

	ds3232->regmap = regmap;
	ds3232->irq = irq;
	ds3232->dev = dev;
	dev_set_drvdata(dev, ds3232);

	ret = ds3232_check_rtc_status(dev);
	if (ret)
		return ret;

	if (ds3232->irq > 0)
		device_init_wakeup(dev, 1);

	ds3232_hwmon_register(dev, name);

	ds3232->rtc = devm_rtc_device_register(dev, name, &ds3232_rtc_ops,
						THIS_MODULE);
	if (IS_ERR(ds3232->rtc))
		return PTR_ERR(ds3232->rtc);

	ret = rtc_nvmem_register(ds3232->rtc, &nvmem_cfg);
	if(ret)
		return ret;

	if (ds3232->irq > 0) {
		ret = devm_request_threaded_irq(dev, ds3232->irq, NULL,
						ds3232_irq,
						IRQF_SHARED | IRQF_ONESHOT,
						name, dev);
		if (ret) {
			device_set_wakeup_capable(dev, 0);
			ds3232->irq = 0;
			dev_err(dev, "unable to request IRQ\n");
		}
	}

	return 0;
}