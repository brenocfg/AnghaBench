#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct spi_device {int bits_per_word; TYPE_2__ dev; int /*<<< orphan*/  mode; } ;
struct max1111_data {int lsb; int /*<<< orphan*/  hwmon_dev; struct spi_device* spi; int /*<<< orphan*/  drvdata_lock; void* sel_sh; } ;
typedef  enum chips { ____Placeholder_chips } chips ;
struct TYPE_5__ {int driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* MAX1110_CTRL_SEL_SH ; 
 void* MAX1111_CTRL_SEL_SH ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct max1111_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_2__*) ; 
#define  max1110 131 
 int /*<<< orphan*/  max1110_attr_group ; 
#define  max1111 130 
 int /*<<< orphan*/  max1111_attr_group ; 
#define  max1112 129 
#define  max1113 128 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int setup_transfer (struct max1111_data*) ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct max1111_data*) ; 
 int spi_setup (struct spi_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct max1111_data* the_max1111 ; 

__attribute__((used)) static int max1111_probe(struct spi_device *spi)
{
	enum chips chip = spi_get_device_id(spi)->driver_data;
	struct max1111_data *data;
	int err;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	err = spi_setup(spi);
	if (err < 0)
		return err;

	data = devm_kzalloc(&spi->dev, sizeof(struct max1111_data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	switch (chip) {
	case max1110:
		data->lsb = 8;
		data->sel_sh = MAX1110_CTRL_SEL_SH;
		break;
	case max1111:
		data->lsb = 8;
		data->sel_sh = MAX1111_CTRL_SEL_SH;
		break;
	case max1112:
		data->lsb = 16;
		data->sel_sh = MAX1110_CTRL_SEL_SH;
		break;
	case max1113:
		data->lsb = 16;
		data->sel_sh = MAX1111_CTRL_SEL_SH;
		break;
	}
	err = setup_transfer(data);
	if (err)
		return err;

	mutex_init(&data->drvdata_lock);

	data->spi = spi;
	spi_set_drvdata(spi, data);

	err = sysfs_create_group(&spi->dev.kobj, &max1111_attr_group);
	if (err) {
		dev_err(&spi->dev, "failed to create attribute group\n");
		return err;
	}
	if (chip == max1110 || chip == max1112) {
		err = sysfs_create_group(&spi->dev.kobj, &max1110_attr_group);
		if (err) {
			dev_err(&spi->dev,
				"failed to create extended attribute group\n");
			goto err_remove;
		}
	}

	data->hwmon_dev = hwmon_device_register(&spi->dev);
	if (IS_ERR(data->hwmon_dev)) {
		dev_err(&spi->dev, "failed to create hwmon device\n");
		err = PTR_ERR(data->hwmon_dev);
		goto err_remove;
	}

#ifdef CONFIG_SHARPSL_PM
	the_max1111 = data;
#endif
	return 0;

err_remove:
	sysfs_remove_group(&spi->dev.kobj, &max1110_attr_group);
	sysfs_remove_group(&spi->dev.kobj, &max1111_attr_group);
	return err;
}