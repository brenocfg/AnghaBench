#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pcf85x63_config {int num_nvram; int /*<<< orphan*/  regmap; } ;
struct pcf85363 {TYPE_1__* rtc; TYPE_1__* regmap; } ;
struct nvmem_config {char* name; int word_size; int stride; int size; struct pcf85363* priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_FLAGS ; 
 int /*<<< orphan*/  CTRL_PIN_IO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
#define  NVRAM_SIZE 132 
 int /*<<< orphan*/  PIN_IO_INTAPM ; 
 int /*<<< orphan*/  PIN_IO_INTA_OUT ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_2000 ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_END_2099 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct pcf85363* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct i2c_client*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf85363*) ; 
 void* of_device_get_match_data (int /*<<< orphan*/ *) ; 
#define  pcf85363_nvram_read 131 
#define  pcf85363_nvram_write 130 
 int /*<<< orphan*/  pcf85363_rtc_handle_irq ; 
#define  pcf85x63_nvram_read 129 
#define  pcf85x63_nvram_write 128 
 struct pcf85x63_config pcf_85363_config ; 
 int /*<<< orphan*/  regmap_update_bits (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int /*<<< orphan*/  rtc_ops ; 
 int /*<<< orphan*/  rtc_ops_alarm ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int pcf85363_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct pcf85363 *pcf85363;
	const struct pcf85x63_config *config = &pcf_85363_config;
	const void *data = of_device_get_match_data(&client->dev);
	static struct nvmem_config nvmem_cfg[] = {
		{
			.name = "pcf85x63-",
			.word_size = 1,
			.stride = 1,
			.size = 1,
			.reg_read = pcf85x63_nvram_read,
			.reg_write = pcf85x63_nvram_write,
		}, {
			.name = "pcf85363-",
			.word_size = 1,
			.stride = 1,
			.size = NVRAM_SIZE,
			.reg_read = pcf85363_nvram_read,
			.reg_write = pcf85363_nvram_write,
		},
	};
	int ret, i;

	if (data)
		config = data;

	pcf85363 = devm_kzalloc(&client->dev, sizeof(struct pcf85363),
				GFP_KERNEL);
	if (!pcf85363)
		return -ENOMEM;

	pcf85363->regmap = devm_regmap_init_i2c(client, &config->regmap);
	if (IS_ERR(pcf85363->regmap)) {
		dev_err(&client->dev, "regmap allocation failed\n");
		return PTR_ERR(pcf85363->regmap);
	}

	i2c_set_clientdata(client, pcf85363);

	pcf85363->rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(pcf85363->rtc))
		return PTR_ERR(pcf85363->rtc);

	pcf85363->rtc->ops = &rtc_ops;
	pcf85363->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	pcf85363->rtc->range_max = RTC_TIMESTAMP_END_2099;

	if (client->irq > 0) {
		regmap_write(pcf85363->regmap, CTRL_FLAGS, 0);
		regmap_update_bits(pcf85363->regmap, CTRL_PIN_IO,
				   PIN_IO_INTA_OUT, PIN_IO_INTAPM);
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL, pcf85363_rtc_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"pcf85363", client);
		if (ret)
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
		else
			pcf85363->rtc->ops = &rtc_ops_alarm;
	}

	ret = rtc_register_device(pcf85363->rtc);

	for (i = 0; i < config->num_nvram; i++) {
		nvmem_cfg[i].priv = pcf85363;
		rtc_nvmem_register(pcf85363->rtc, &nvmem_cfg[i]);
	}

	return ret;
}