#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rv3028_data {TYPE_2__* rtc; int /*<<< orphan*/  regmap; } ;
struct nvmem_config {char* name; int word_size; int stride; int size; int /*<<< orphan*/  priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  type; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int max_user_freq; TYPE_1__* ops; int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; } ;
struct TYPE_8__ {int /*<<< orphan*/  alarm_irq_enable; int /*<<< orphan*/  set_alarm; int /*<<< orphan*/  read_alarm; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  NVMEM_TYPE_BATTERY_BACKED ; 
 int /*<<< orphan*/  NVMEM_TYPE_EEPROM ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_2000 ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_END_2099 ; 
 int /*<<< orphan*/  RV3028_BACKUP ; 
 int RV3028_BACKUP_TCE ; 
 int RV3028_BACKUP_TCR_MASK ; 
 int /*<<< orphan*/  RV3028_CTRL1 ; 
 int RV3028_CTRL1_WADA ; 
 int /*<<< orphan*/  RV3028_CTRL2 ; 
 int RV3028_CTRL2_EIE ; 
 int RV3028_CTRL2_TSE ; 
 int /*<<< orphan*/  RV3028_STATUS ; 
 int RV3028_STATUS_AF ; 
 int RV3028_STATUS_PORF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 struct rv3028_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct rv3028_data*) ; 
 TYPE_2__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rv3028_data*) ; 
 int /*<<< orphan*/  regmap_config ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int rtc_add_group (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_2__*,struct nvmem_config*) ; 
 int rtc_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rv3028_alarm_irq_enable ; 
 int /*<<< orphan*/  rv3028_attr_group ; 
 int /*<<< orphan*/  rv3028_eeprom_read ; 
 int /*<<< orphan*/  rv3028_eeprom_write ; 
 int /*<<< orphan*/  rv3028_get_alarm ; 
 int /*<<< orphan*/  rv3028_handle_irq ; 
 int /*<<< orphan*/  rv3028_nvram_read ; 
 int /*<<< orphan*/  rv3028_nvram_write ; 
 TYPE_1__ rv3028_rtc_ops ; 
 int /*<<< orphan*/  rv3028_set_alarm ; 
 scalar_t__* rv3028_trickle_resistors ; 

__attribute__((used)) static int rv3028_probe(struct i2c_client *client)
{
	struct rv3028_data *rv3028;
	int ret, status;
	u32 ohms;
	struct nvmem_config nvmem_cfg = {
		.name = "rv3028_nvram",
		.word_size = 1,
		.stride = 1,
		.size = 2,
		.type = NVMEM_TYPE_BATTERY_BACKED,
		.reg_read = rv3028_nvram_read,
		.reg_write = rv3028_nvram_write,
	};
	struct nvmem_config eeprom_cfg = {
		.name = "rv3028_eeprom",
		.word_size = 1,
		.stride = 1,
		.size = 43,
		.type = NVMEM_TYPE_EEPROM,
		.reg_read = rv3028_eeprom_read,
		.reg_write = rv3028_eeprom_write,
	};

	rv3028 = devm_kzalloc(&client->dev, sizeof(struct rv3028_data),
			      GFP_KERNEL);
	if (!rv3028)
		return -ENOMEM;

	rv3028->regmap = devm_regmap_init_i2c(client, &regmap_config);

	i2c_set_clientdata(client, rv3028);

	ret = regmap_read(rv3028->regmap, RV3028_STATUS, &status);
	if (ret < 0)
		return ret;

	if (status & RV3028_STATUS_PORF)
		dev_warn(&client->dev, "Voltage low, data loss detected.\n");

	if (status & RV3028_STATUS_AF)
		dev_warn(&client->dev, "An alarm may have been missed.\n");

	rv3028->rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(rv3028->rtc))
		return PTR_ERR(rv3028->rtc);

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL, rv3028_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"rv3028", rv3028);
		if (ret) {
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		} else {
			rv3028_rtc_ops.read_alarm = rv3028_get_alarm;
			rv3028_rtc_ops.set_alarm = rv3028_set_alarm;
			rv3028_rtc_ops.alarm_irq_enable = rv3028_alarm_irq_enable;
		}
	}

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL1,
				 RV3028_CTRL1_WADA, RV3028_CTRL1_WADA);
	if (ret)
		return ret;

	/* setup timestamping */
	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_EIE | RV3028_CTRL2_TSE,
				 RV3028_CTRL2_EIE | RV3028_CTRL2_TSE);
	if (ret)
		return ret;

	/* setup trickle charger */
	if (!device_property_read_u32(&client->dev, "trickle-resistor-ohms",
				      &ohms)) {
		int i;

		for (i = 0; i < ARRAY_SIZE(rv3028_trickle_resistors); i++)
			if (ohms == rv3028_trickle_resistors[i])
				break;

		if (i < ARRAY_SIZE(rv3028_trickle_resistors)) {
			ret = regmap_update_bits(rv3028->regmap, RV3028_BACKUP,
						 RV3028_BACKUP_TCE |
						 RV3028_BACKUP_TCR_MASK,
						 RV3028_BACKUP_TCE | i);
			if (ret)
				return ret;
		} else {
			dev_warn(&client->dev, "invalid trickle resistor value\n");
		}
	}

	ret = rtc_add_group(rv3028->rtc, &rv3028_attr_group);
	if (ret)
		return ret;

	rv3028->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rv3028->rtc->range_max = RTC_TIMESTAMP_END_2099;
	rv3028->rtc->ops = &rv3028_rtc_ops;
	ret = rtc_register_device(rv3028->rtc);
	if (ret)
		return ret;

	nvmem_cfg.priv = rv3028->regmap;
	rtc_nvmem_register(rv3028->rtc, &nvmem_cfg);
	eeprom_cfg.priv = rv3028->regmap;
	rtc_nvmem_register(rv3028->rtc, &eeprom_cfg);

	rv3028->rtc->max_user_freq = 1;

	return 0;
}