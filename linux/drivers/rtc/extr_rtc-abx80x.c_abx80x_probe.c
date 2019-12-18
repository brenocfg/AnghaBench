#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {unsigned int driver_data; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct i2c_client {int irq; TYPE_4__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;
struct abx80x_priv {TYPE_1__* rtc; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_14__ {int pn; scalar_t__ has_wdog; scalar_t__ has_tc; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 unsigned int ABX80X ; 
 int ABX8XX_CFG_KEY_MISC ; 
 int ABX8XX_CTRL2_RSVD ; 
 int ABX8XX_CTRL_12_24 ; 
 int ABX8XX_CTRL_ARST ; 
 int ABX8XX_CTRL_WRITE ; 
 int ABX8XX_OUT_CTRL_EXDS ; 
 int /*<<< orphan*/  ABX8XX_REG_CD_TIMER_CTL ; 
 int /*<<< orphan*/  ABX8XX_REG_CFG_KEY ; 
 int /*<<< orphan*/  ABX8XX_REG_CTRL1 ; 
 int /*<<< orphan*/  ABX8XX_REG_CTRL2 ; 
 int /*<<< orphan*/  ABX8XX_REG_ID0 ; 
 int /*<<< orphan*/  ABX8XX_REG_OUT_CTRL ; 
 int BIT (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 unsigned int RV1805 ; 
 TYPE_9__* abx80x_caps ; 
 int abx80x_dt_trickle_cfg (struct device_node*) ; 
 int /*<<< orphan*/  abx80x_enable_trickle_charger (struct i2c_client*,int) ; 
 int /*<<< orphan*/  abx80x_handle_irq ; 
 int /*<<< orphan*/  abx80x_rtc_ops ; 
 int abx80x_setup_watchdog (struct abx80x_priv*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int,...) ; 
 struct abx80x_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct i2c_client*) ; 
 TYPE_1__* devm_rtc_allocate_device (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct abx80x_priv*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int rtc_add_group (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_calib_attr_group ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int abx80x_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device_node *np = client->dev.of_node;
	struct abx80x_priv *priv;
	int i, data, err, trickle_cfg = -EINVAL;
	char buf[7];
	unsigned int part = id->driver_data;
	unsigned int partnumber;
	unsigned int majrev, minrev;
	unsigned int lot;
	unsigned int wafer;
	unsigned int uid;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	err = i2c_smbus_read_i2c_block_data(client, ABX8XX_REG_ID0,
					    sizeof(buf), buf);
	if (err < 0) {
		dev_err(&client->dev, "Unable to read partnumber\n");
		return -EIO;
	}

	partnumber = (buf[0] << 8) | buf[1];
	majrev = buf[2] >> 3;
	minrev = buf[2] & 0x7;
	lot = ((buf[4] & 0x80) << 2) | ((buf[6] & 0x80) << 1) | buf[3];
	uid = ((buf[4] & 0x7f) << 8) | buf[5];
	wafer = (buf[6] & 0x7c) >> 2;
	dev_info(&client->dev, "model %04x, revision %u.%u, lot %x, wafer %x, uid %x\n",
		 partnumber, majrev, minrev, lot, wafer, uid);

	data = i2c_smbus_read_byte_data(client, ABX8XX_REG_CTRL1);
	if (data < 0) {
		dev_err(&client->dev, "Unable to read control register\n");
		return -EIO;
	}

	err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CTRL1,
					((data & ~(ABX8XX_CTRL_12_24 |
						   ABX8XX_CTRL_ARST)) |
					 ABX8XX_CTRL_WRITE));
	if (err < 0) {
		dev_err(&client->dev, "Unable to write control register\n");
		return -EIO;
	}

	/* Configure RV1805 specifics */
	if (part == RV1805) {
		/*
		 * Avoid accidentally entering test mode. This can happen
		 * on the RV1805 in case the reserved bit 5 in control2
		 * register is set. RV-1805-C3 datasheet indicates that
		 * the bit should be cleared in section 11h - Control2.
		 */
		data = i2c_smbus_read_byte_data(client, ABX8XX_REG_CTRL2);
		if (data < 0) {
			dev_err(&client->dev,
				"Unable to read control2 register\n");
			return -EIO;
		}

		err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CTRL2,
						data & ~ABX8XX_CTRL2_RSVD);
		if (err < 0) {
			dev_err(&client->dev,
				"Unable to write control2 register\n");
			return -EIO;
		}

		/*
		 * Avoid extra power leakage. The RV1805 uses smaller
		 * 10pin package and the EXTI input is not present.
		 * Disable it to avoid leakage.
		 */
		data = i2c_smbus_read_byte_data(client, ABX8XX_REG_OUT_CTRL);
		if (data < 0) {
			dev_err(&client->dev,
				"Unable to read output control register\n");
			return -EIO;
		}

		/*
		 * Write the configuration key register to enable access to
		 * the config2 register
		 */
		err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CFG_KEY,
						ABX8XX_CFG_KEY_MISC);
		if (err < 0) {
			dev_err(&client->dev,
				"Unable to write configuration key\n");
			return -EIO;
		}

		err = i2c_smbus_write_byte_data(client, ABX8XX_REG_OUT_CTRL,
						data | ABX8XX_OUT_CTRL_EXDS);
		if (err < 0) {
			dev_err(&client->dev,
				"Unable to write output control register\n");
			return -EIO;
		}
	}

	/* part autodetection */
	if (part == ABX80X) {
		for (i = 0; abx80x_caps[i].pn; i++)
			if (partnumber == abx80x_caps[i].pn)
				break;
		if (abx80x_caps[i].pn == 0) {
			dev_err(&client->dev, "Unknown part: %04x\n",
				partnumber);
			return -EINVAL;
		}
		part = i;
	}

	if (partnumber != abx80x_caps[part].pn) {
		dev_err(&client->dev, "partnumber mismatch %04x != %04x\n",
			partnumber, abx80x_caps[part].pn);
		return -EINVAL;
	}

	if (np && abx80x_caps[part].has_tc)
		trickle_cfg = abx80x_dt_trickle_cfg(np);

	if (trickle_cfg > 0) {
		dev_info(&client->dev, "Enabling trickle charger: %02x\n",
			 trickle_cfg);
		abx80x_enable_trickle_charger(client, trickle_cfg);
	}

	err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CD_TIMER_CTL,
					BIT(2));
	if (err)
		return err;

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	priv->rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(priv->rtc))
		return PTR_ERR(priv->rtc);

	priv->rtc->ops = &abx80x_rtc_ops;
	priv->client = client;

	i2c_set_clientdata(client, priv);

	if (abx80x_caps[part].has_wdog) {
		err = abx80x_setup_watchdog(priv);
		if (err)
			return err;
	}

	if (client->irq > 0) {
		dev_info(&client->dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_threaded_irq(&client->dev, client->irq, NULL,
						abx80x_handle_irq,
						IRQF_SHARED | IRQF_ONESHOT,
						"abx8xx",
						client);
		if (err) {
			dev_err(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		}
	}

	err = rtc_add_group(priv->rtc, &rtc_calib_attr_group);
	if (err) {
		dev_err(&client->dev, "Failed to create sysfs group: %d\n",
			err);
		return err;
	}

	return rtc_register_device(priv->rtc);
}