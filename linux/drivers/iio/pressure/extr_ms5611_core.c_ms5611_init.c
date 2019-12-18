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
struct ms5611_state {int /*<<< orphan*/  vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 struct ms5611_state* iio_priv (struct iio_dev*) ; 
 int ms5611_read_prom (struct iio_dev*) ; 
 int ms5611_reset (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms5611_init(struct iio_dev *indio_dev)
{
	int ret;
	struct ms5611_state *st = iio_priv(indio_dev);

	/* Enable attached regulator if any. */
	st->vdd = devm_regulator_get(indio_dev->dev.parent, "vdd");
	if (IS_ERR(st->vdd))
		return PTR_ERR(st->vdd);

	ret = regulator_enable(st->vdd);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"failed to enable Vdd supply: %d\n", ret);
		return ret;
	}

	ret = ms5611_reset(indio_dev);
	if (ret < 0)
		goto err_regulator_disable;

	ret = ms5611_read_prom(indio_dev);
	if (ret < 0)
		goto err_regulator_disable;

	return 0;

err_regulator_disable:
	regulator_disable(st->vdd);
	return ret;
}