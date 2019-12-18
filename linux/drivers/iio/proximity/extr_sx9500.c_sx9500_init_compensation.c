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
struct sx9500_data {int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SX9500_CHAN_MASK ; 
 unsigned int SX9500_COMPSTAT_MASK ; 
 int /*<<< orphan*/  SX9500_REG_PROX_CTRL0 ; 
 int /*<<< orphan*/  SX9500_REG_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sx9500_init_compensation(struct iio_dev *indio_dev)
{
	struct sx9500_data *data = iio_priv(indio_dev);
	int i, ret;
	unsigned int val;

	ret = regmap_update_bits(data->regmap, SX9500_REG_PROX_CTRL0,
				 SX9500_CHAN_MASK, SX9500_CHAN_MASK);
	if (ret < 0)
		return ret;

	for (i = 10; i >= 0; i--) {
		usleep_range(10000, 20000);
		ret = regmap_read(data->regmap, SX9500_REG_STAT, &val);
		if (ret < 0)
			goto out;
		if (!(val & SX9500_COMPSTAT_MASK))
			break;
	}

	if (i < 0) {
		dev_err(&data->client->dev, "initial compensation timed out");
		ret = -ETIMEDOUT;
	}

out:
	regmap_update_bits(data->regmap, SX9500_REG_PROX_CTRL0,
			   SX9500_CHAN_MASK, 0);
	return ret;
}