#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct hym8563 {int valid; TYPE_1__* rtc; struct i2c_client* client; } ;
struct TYPE_4__ {int uie_unsupported; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HYM8563_SEC ; 
 int HYM8563_SEC_VL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 struct hym8563* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hym8563*) ; 
 TYPE_1__* devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hym8563_clkout_register_clk (struct hym8563*) ; 
 int hym8563_init_device (struct i2c_client*) ; 
 int /*<<< orphan*/  hym8563_irq ; 
 int /*<<< orphan*/  hym8563_rtc_ops ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct hym8563*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hym8563_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct hym8563 *hym8563;
	int ret;

	hym8563 = devm_kzalloc(&client->dev, sizeof(*hym8563), GFP_KERNEL);
	if (!hym8563)
		return -ENOMEM;

	hym8563->client = client;
	i2c_set_clientdata(client, hym8563);

	device_set_wakeup_capable(&client->dev, true);

	ret = hym8563_init_device(client);
	if (ret) {
		dev_err(&client->dev, "could not init device, %d\n", ret);
		return ret;
	}

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL, hym8563_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, hym8563);
		if (ret < 0) {
			dev_err(&client->dev, "irq %d request failed, %d\n",
				client->irq, ret);
			return ret;
		}
	}

	/* check state of calendar information */
	ret = i2c_smbus_read_byte_data(client, HYM8563_SEC);
	if (ret < 0)
		return ret;

	hym8563->valid = !(ret & HYM8563_SEC_VL);
	dev_dbg(&client->dev, "rtc information is %s\n",
		hym8563->valid ? "valid" : "invalid");

	hym8563->rtc = devm_rtc_device_register(&client->dev, client->name,
						&hym8563_rtc_ops, THIS_MODULE);
	if (IS_ERR(hym8563->rtc))
		return PTR_ERR(hym8563->rtc);

	/* the hym8563 alarm only supports a minute accuracy */
	hym8563->rtc->uie_unsupported = 1;

#ifdef CONFIG_COMMON_CLK
	hym8563_clkout_register_clk(hym8563);
#endif

	return 0;
}