#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tle62x0_state {int nr_gpio; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_state; struct spi_device* us; } ;
struct tle62x0_pdata {int gpio_count; int /*<<< orphan*/  init_state; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_status_show ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tle62x0_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** gpio_attrs ; 
 int /*<<< orphan*/  kfree (struct tle62x0_state*) ; 
 struct tle62x0_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct tle62x0_state*) ; 

__attribute__((used)) static int tle62x0_probe(struct spi_device *spi)
{
	struct tle62x0_state *st;
	struct tle62x0_pdata *pdata;
	int ptr;
	int ret;

	pdata = dev_get_platdata(&spi->dev);
	if (pdata == NULL) {
		dev_err(&spi->dev, "no device data specified\n");
		return -EINVAL;
	}

	st = kzalloc(sizeof(struct tle62x0_state), GFP_KERNEL);
	if (st == NULL)
		return -ENOMEM;

	st->us = spi;
	st->nr_gpio = pdata->gpio_count;
	st->gpio_state = pdata->init_state;

	mutex_init(&st->lock);

	ret = device_create_file(&spi->dev, &dev_attr_status_show);
	if (ret) {
		dev_err(&spi->dev, "cannot create status attribute\n");
		goto err_status;
	}

	for (ptr = 0; ptr < pdata->gpio_count; ptr++) {
		ret = device_create_file(&spi->dev, gpio_attrs[ptr]);
		if (ret) {
			dev_err(&spi->dev, "cannot create gpio attribute\n");
			goto err_gpios;
		}
	}

	/* tle62x0_write(st); */
	spi_set_drvdata(spi, st);
	return 0;

 err_gpios:
	while (--ptr >= 0)
		device_remove_file(&spi->dev, gpio_attrs[ptr]);

	device_remove_file(&spi->dev, &dev_attr_status_show);

 err_status:
	kfree(st);
	return ret;
}