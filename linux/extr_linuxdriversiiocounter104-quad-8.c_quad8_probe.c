#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct quad8_iio {int base; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  channels; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int QUAD8_CHAN_OP_ENABLE_COUNTERS ; 
 int QUAD8_CHAN_OP_RESET_COUNTERS ; 
 int QUAD8_CTR_CMR ; 
 int QUAD8_CTR_IDR ; 
 int QUAD8_CTR_IOR ; 
 int QUAD8_CTR_RLD ; 
 scalar_t__ QUAD8_EXTENT ; 
 int QUAD8_NUM_COUNTERS ; 
 int QUAD8_REG_CHAN_OP ; 
 int QUAD8_RLD_RESET_BP ; 
 int QUAD8_RLD_RESET_E ; 
 int QUAD8_RLD_RESET_FLAGS ; 
 int* base ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  quad8_channels ; 
 int /*<<< orphan*/  quad8_info ; 

__attribute__((used)) static int quad8_probe(struct device *dev, unsigned int id)
{
	struct iio_dev *indio_dev;
	struct quad8_iio *priv;
	int i, j;
	unsigned int base_offset;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*priv));
	if (!indio_dev)
		return -ENOMEM;

	if (!devm_request_region(dev, base[id], QUAD8_EXTENT,
		dev_name(dev))) {
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + QUAD8_EXTENT);
		return -EBUSY;
	}

	indio_dev->info = &quad8_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->num_channels = ARRAY_SIZE(quad8_channels);
	indio_dev->channels = quad8_channels;
	indio_dev->name = dev_name(dev);
	indio_dev->dev.parent = dev;

	priv = iio_priv(indio_dev);
	priv->base = base[id];

	/* Reset all counters and disable interrupt function */
	outb(QUAD8_CHAN_OP_RESET_COUNTERS, base[id] + QUAD8_REG_CHAN_OP);
	/* Set initial configuration for all counters */
	for (i = 0; i < QUAD8_NUM_COUNTERS; i++) {
		base_offset = base[id] + 2 * i;
		/* Reset Byte Pointer */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);
		/* Reset Preset Register */
		for (j = 0; j < 3; j++)
			outb(0x00, base_offset);
		/* Reset Borrow, Carry, Compare, and Sign flags */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_FLAGS, base_offset + 1);
		/* Reset Error flag */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_E, base_offset + 1);
		/* Binary encoding; Normal count; non-quadrature mode */
		outb(QUAD8_CTR_CMR, base_offset + 1);
		/* Disable A and B inputs; preset on index; FLG1 as Carry */
		outb(QUAD8_CTR_IOR, base_offset + 1);
		/* Disable index function; negative index polarity */
		outb(QUAD8_CTR_IDR, base_offset + 1);
	}
	/* Enable all counters */
	outb(QUAD8_CHAN_OP_ENABLE_COUNTERS, base[id] + QUAD8_REG_CHAN_OP);

	return devm_iio_device_register(dev, indio_dev);
}