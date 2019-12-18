#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct pcf857x_platform_data {unsigned int n_latch; int gpio_base; int (* setup ) (struct i2c_client*,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; } ;
struct TYPE_15__ {int base; int can_sleep; int ngpio; int /*<<< orphan*/  label; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  owner; TYPE_5__* parent; } ;
struct TYPE_16__ {char* name; int /*<<< orphan*/  irq_bus_sync_unlock; int /*<<< orphan*/  irq_bus_lock; int /*<<< orphan*/  irq_set_wake; void* irq_unmask; void* irq_mask; void* irq_ack; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; } ;
struct pcf857x {int (* read ) (struct i2c_client*) ;unsigned int out; unsigned int status; TYPE_1__ chip; TYPE_2__ irqchip; struct i2c_client* client; int /*<<< orphan*/  write; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_17__ {struct device_node* of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; TYPE_5__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 struct pcf857x_platform_data* dev_get_platdata (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_5__*,char*,int) ; 
 int devm_gpiochip_add_data (TYPE_5__*,TYPE_1__*,struct pcf857x*) ; 
 struct pcf857x* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct pcf857x*) ; 
 int gpiochip_irqchip_add_nested (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_nested_irqchip (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_read_le16 (struct i2c_client*) ; 
 int i2c_read_le8 (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf857x*) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_write_le16 ; 
 int /*<<< orphan*/  i2c_write_le8 ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* noop ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int /*<<< orphan*/  pcf857x_get ; 
 int /*<<< orphan*/  pcf857x_input ; 
 int /*<<< orphan*/  pcf857x_irq ; 
 int /*<<< orphan*/  pcf857x_irq_bus_lock ; 
 int /*<<< orphan*/  pcf857x_irq_bus_sync_unlock ; 
 int /*<<< orphan*/  pcf857x_irq_disable ; 
 int /*<<< orphan*/  pcf857x_irq_enable ; 
 int /*<<< orphan*/  pcf857x_irq_set_wake ; 
 int /*<<< orphan*/  pcf857x_output ; 
 int /*<<< orphan*/  pcf857x_set ; 
 int stub1 (struct i2c_client*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf857x_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct pcf857x_platform_data	*pdata = dev_get_platdata(&client->dev);
	struct device_node		*np = client->dev.of_node;
	struct pcf857x			*gpio;
	unsigned int			n_latch = 0;
	int				status;

	if (IS_ENABLED(CONFIG_OF) && np)
		of_property_read_u32(np, "lines-initial-states", &n_latch);
	else if (pdata)
		n_latch = pdata->n_latch;
	else
		dev_dbg(&client->dev, "no platform data\n");

	/* Allocate, initialize, and register this gpio_chip. */
	gpio = devm_kzalloc(&client->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	mutex_init(&gpio->lock);

	gpio->chip.base			= pdata ? pdata->gpio_base : -1;
	gpio->chip.can_sleep		= true;
	gpio->chip.parent		= &client->dev;
	gpio->chip.owner		= THIS_MODULE;
	gpio->chip.get			= pcf857x_get;
	gpio->chip.set			= pcf857x_set;
	gpio->chip.direction_input	= pcf857x_input;
	gpio->chip.direction_output	= pcf857x_output;
	gpio->chip.ngpio		= id->driver_data;

	/* NOTE:  the OnSemi jlc1562b is also largely compatible with
	 * these parts, notably for output.  It has a low-resolution
	 * DAC instead of pin change IRQs; and its inputs can be the
	 * result of comparators.
	 */

	/* 8574 addresses are 0x20..0x27; 8574a uses 0x38..0x3f;
	 * 9670, 9672, 9764, and 9764a use quite a variety.
	 *
	 * NOTE: we don't distinguish here between *4 and *4a parts.
	 */
	if (gpio->chip.ngpio == 8) {
		gpio->write	= i2c_write_le8;
		gpio->read	= i2c_read_le8;

		if (!i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE))
			status = -EIO;

		/* fail if there's no chip present */
		else
			status = i2c_smbus_read_byte(client);

	/* '75/'75c addresses are 0x20..0x27, just like the '74;
	 * the '75c doesn't have a current source pulling high.
	 * 9671, 9673, and 9765 use quite a variety of addresses.
	 *
	 * NOTE: we don't distinguish here between '75 and '75c parts.
	 */
	} else if (gpio->chip.ngpio == 16) {
		gpio->write	= i2c_write_le16;
		gpio->read	= i2c_read_le16;

		if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
			status = -EIO;

		/* fail if there's no chip present */
		else
			status = i2c_read_le16(client);

	} else {
		dev_dbg(&client->dev, "unsupported number of gpios\n");
		status = -EINVAL;
	}

	if (status < 0)
		goto fail;

	gpio->chip.label = client->name;

	gpio->client = client;
	i2c_set_clientdata(client, gpio);

	/* NOTE:  these chips have strange "quasi-bidirectional" I/O pins.
	 * We can't actually know whether a pin is configured (a) as output
	 * and driving the signal low, or (b) as input and reporting a low
	 * value ... without knowing the last value written since the chip
	 * came out of reset (if any).  We can't read the latched output.
	 *
	 * In short, the only reliable solution for setting up pin direction
	 * is to do it explicitly.  The setup() method can do that, but it
	 * may cause transient glitching since it can't know the last value
	 * written (some pins may need to be driven low).
	 *
	 * Using n_latch avoids that trouble.  When left initialized to zero,
	 * our software copy of the "latch" then matches the chip's all-ones
	 * reset state.  Otherwise it flags pins to be driven low.
	 */
	gpio->out = ~n_latch;
	gpio->status = gpio->out;

	status = devm_gpiochip_add_data(&client->dev, &gpio->chip, gpio);
	if (status < 0)
		goto fail;

	/* Enable irqchip if we have an interrupt */
	if (client->irq) {
		gpio->irqchip.name = "pcf857x",
		gpio->irqchip.irq_enable = pcf857x_irq_enable,
		gpio->irqchip.irq_disable = pcf857x_irq_disable,
		gpio->irqchip.irq_ack = noop,
		gpio->irqchip.irq_mask = noop,
		gpio->irqchip.irq_unmask = noop,
		gpio->irqchip.irq_set_wake = pcf857x_irq_set_wake,
		gpio->irqchip.irq_bus_lock = pcf857x_irq_bus_lock,
		gpio->irqchip.irq_bus_sync_unlock = pcf857x_irq_bus_sync_unlock,
		status = gpiochip_irqchip_add_nested(&gpio->chip,
						     &gpio->irqchip,
						     0, handle_level_irq,
						     IRQ_TYPE_NONE);
		if (status) {
			dev_err(&client->dev, "cannot add irqchip\n");
			goto fail;
		}

		status = devm_request_threaded_irq(&client->dev, client->irq,
					NULL, pcf857x_irq, IRQF_ONESHOT |
					IRQF_TRIGGER_FALLING | IRQF_SHARED,
					dev_name(&client->dev), gpio);
		if (status)
			goto fail;

		gpiochip_set_nested_irqchip(&gpio->chip, &gpio->irqchip,
					    client->irq);
	}

	/* Let platform code set up the GPIOs and their users.
	 * Now is the first time anyone could use them.
	 */
	if (pdata && pdata->setup) {
		status = pdata->setup(client,
				gpio->chip.base, gpio->chip.ngpio,
				pdata->context);
		if (status < 0)
			dev_warn(&client->dev, "setup --> %d\n", status);
	}

	dev_info(&client->dev, "probed\n");

	return 0;

fail:
	dev_dbg(&client->dev, "probe error %d for '%s'\n", status,
		client->name);

	return status;
}