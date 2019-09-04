#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct input_polled_dev {TYPE_2__* input; int /*<<< orphan*/  poll; struct gpio_decoder* private; } ;
struct gpio_decoder {unsigned int axis; struct input_polled_dev* poll_dev; struct device* dev; TYPE_3__* input_gpios; } ;
struct TYPE_8__ {int ndescs; } ;
struct TYPE_6__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_7__ {TYPE_1__ id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,unsigned int*) ; 
 TYPE_3__* devm_gpiod_get_array (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct input_polled_dev* devm_input_allocate_polled_device (struct device*) ; 
 struct gpio_decoder* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_decoder_poll_gpios ; 
 int input_register_polled_device (struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_decoder_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct gpio_decoder *decoder;
	struct input_polled_dev *poll_dev;
	u32  max;
	int err;

	decoder = devm_kzalloc(dev, sizeof(struct gpio_decoder), GFP_KERNEL);
	if (!decoder)
		return -ENOMEM;

	device_property_read_u32(dev, "linux,axis", &decoder->axis);
	decoder->input_gpios = devm_gpiod_get_array(dev, NULL, GPIOD_IN);
	if (IS_ERR(decoder->input_gpios)) {
		dev_err(dev, "unable to acquire input gpios\n");
		return PTR_ERR(decoder->input_gpios);
	}
	if (decoder->input_gpios->ndescs < 2) {
		dev_err(dev, "not enough gpios found\n");
		return -EINVAL;
	}

	if (device_property_read_u32(dev, "decoder-max-value", &max))
		max = (1U << decoder->input_gpios->ndescs) - 1;

	decoder->dev = dev;
	poll_dev = devm_input_allocate_polled_device(decoder->dev);
	if (!poll_dev)
		return -ENOMEM;

	poll_dev->private = decoder;
	poll_dev->poll = gpio_decoder_poll_gpios;
	decoder->poll_dev = poll_dev;

	poll_dev->input->name = pdev->name;
	poll_dev->input->id.bustype = BUS_HOST;
	input_set_abs_params(poll_dev->input, decoder->axis, 0, max, 0, 0);

	err = input_register_polled_device(poll_dev);
	if (err) {
		dev_err(dev, "failed to register polled  device\n");
		return err;
	}

	return 0;
}