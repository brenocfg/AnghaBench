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
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct input_polled_dev {int poll_interval; struct input_dev* input; struct adc_keys_state* private; int /*<<< orphan*/  poll; } ;
struct TYPE_7__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* phys; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct adc_keys_state {int keyup_voltage; int num_keys; TYPE_2__* map; TYPE_3__* channel; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
struct TYPE_9__ {int /*<<< orphan*/  indio_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IIO_VOLTAGE ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adc_keys_load_keymap (struct device*,struct adc_keys_state*) ; 
 int /*<<< orphan*/  adc_keys_poll ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,int*) ; 
 TYPE_3__* devm_iio_channel_get (struct device*,char*) ; 
 struct input_polled_dev* devm_input_allocate_polled_device (struct device*) ; 
 struct adc_keys_state* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int iio_get_channel_type (TYPE_3__*,int*) ; 
 int input_register_polled_device (struct input_polled_dev*) ; 

__attribute__((used)) static int adc_keys_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct adc_keys_state *st;
	struct input_polled_dev *poll_dev;
	struct input_dev *input;
	enum iio_chan_type type;
	int i, value;
	int error;

	st = devm_kzalloc(dev, sizeof(*st), GFP_KERNEL);
	if (!st)
		return -ENOMEM;

	st->channel = devm_iio_channel_get(dev, "buttons");
	if (IS_ERR(st->channel))
		return PTR_ERR(st->channel);

	if (!st->channel->indio_dev)
		return -ENXIO;

	error = iio_get_channel_type(st->channel, &type);
	if (error < 0)
		return error;

	if (type != IIO_VOLTAGE) {
		dev_err(dev, "Incompatible channel type %d\n", type);
		return -EINVAL;
	}

	if (device_property_read_u32(dev, "keyup-threshold-microvolt",
				     &st->keyup_voltage)) {
		dev_err(dev, "Invalid or missing keyup voltage\n");
		return -EINVAL;
	}
	st->keyup_voltage /= 1000;

	error = adc_keys_load_keymap(dev, st);
	if (error)
		return error;

	poll_dev = devm_input_allocate_polled_device(dev);
	if (!poll_dev) {
		dev_err(dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	if (!device_property_read_u32(dev, "poll-interval", &value))
		poll_dev->poll_interval = value;

	poll_dev->poll = adc_keys_poll;
	poll_dev->private = st;

	input = poll_dev->input;

	input->name = pdev->name;
	input->phys = "adc-keys/input0";

	input->id.bustype = BUS_HOST;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	__set_bit(EV_KEY, input->evbit);
	for (i = 0; i < st->num_keys; i++)
		__set_bit(st->map[i].keycode, input->keybit);

	if (device_property_read_bool(dev, "autorepeat"))
		__set_bit(EV_REP, input->evbit);

	error = input_register_polled_device(poll_dev);
	if (error) {
		dev_err(dev, "Unable to register input device: %d\n", error);
		return error;
	}

	return 0;
}