#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {TYPE_2__ attr; int /*<<< orphan*/  show; } ;
struct sensor_device_attribute {int index; TYPE_1__ dev_attr; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {TYPE_2__** attrs; } ;
struct iio_hwmon_state {size_t num_channels; TYPE_4__** groups; TYPE_4__ attr_group; TYPE_2__** attrs; struct iio_channel* channels; } ;
struct iio_channel {scalar_t__ indio_dev; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IIO_CURRENT 132 
#define  IIO_HUMIDITYRELATIVE 131 
#define  IIO_POWER 130 
#define  IIO_TEMP 129 
#define  IIO_VOLTAGE 128 
 scalar_t__ IS_ERR (struct iio_channel*) ; 
 int PTR_ERR (struct iio_channel*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct iio_hwmon_state*,TYPE_4__**) ; 
 struct iio_channel* devm_iio_channel_get_all (struct device*) ; 
 void* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 TYPE_2__** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int iio_get_channel_type (struct iio_channel*,int*) ; 
 int /*<<< orphan*/  iio_hwmon_read_val ; 
 int /*<<< orphan*/  strreplace (char*,char,char) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static int iio_hwmon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iio_hwmon_state *st;
	struct sensor_device_attribute *a;
	int ret, i;
	int in_i = 1, temp_i = 1, curr_i = 1, humidity_i = 1, power_i = 1;
	enum iio_chan_type type;
	struct iio_channel *channels;
	struct device *hwmon_dev;
	char *sname;

	channels = devm_iio_channel_get_all(dev);
	if (IS_ERR(channels)) {
		if (PTR_ERR(channels) == -ENODEV)
			return -EPROBE_DEFER;
		return PTR_ERR(channels);
	}

	st = devm_kzalloc(dev, sizeof(*st), GFP_KERNEL);
	if (st == NULL)
		return -ENOMEM;

	st->channels = channels;

	/* count how many attributes we have */
	while (st->channels[st->num_channels].indio_dev)
		st->num_channels++;

	st->attrs = devm_kcalloc(dev,
				 st->num_channels + 1, sizeof(*st->attrs),
				 GFP_KERNEL);
	if (st->attrs == NULL)
		return -ENOMEM;

	for (i = 0; i < st->num_channels; i++) {
		const char *prefix;
		int n;

		a = devm_kzalloc(dev, sizeof(*a), GFP_KERNEL);
		if (a == NULL)
			return -ENOMEM;

		sysfs_attr_init(&a->dev_attr.attr);
		ret = iio_get_channel_type(&st->channels[i], &type);
		if (ret < 0)
			return ret;

		switch (type) {
		case IIO_VOLTAGE:
			n = in_i++;
			prefix = "in";
			break;
		case IIO_TEMP:
			n = temp_i++;
			prefix = "temp";
			break;
		case IIO_CURRENT:
			n = curr_i++;
			prefix = "curr";
			break;
		case IIO_POWER:
			n = power_i++;
			prefix = "power";
			break;
		case IIO_HUMIDITYRELATIVE:
			n = humidity_i++;
			prefix = "humidity";
			break;
		default:
			return -EINVAL;
		}

		a->dev_attr.attr.name = devm_kasprintf(dev, GFP_KERNEL,
						       "%s%d_input",
						       prefix, n);
		if (a->dev_attr.attr.name == NULL)
			return -ENOMEM;

		a->dev_attr.show = iio_hwmon_read_val;
		a->dev_attr.attr.mode = 0444;
		a->index = i;
		st->attrs[i] = &a->dev_attr.attr;
	}

	st->attr_group.attrs = st->attrs;
	st->groups[0] = &st->attr_group;

	if (dev->of_node) {
		sname = devm_kasprintf(dev, GFP_KERNEL, "%pOFn", dev->of_node);
		if (!sname)
			return -ENOMEM;
		strreplace(sname, '-', '_');
	} else {
		sname = "iio_hwmon";
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, sname, st,
							   st->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}