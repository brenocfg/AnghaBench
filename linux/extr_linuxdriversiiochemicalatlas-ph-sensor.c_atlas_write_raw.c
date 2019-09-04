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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; int /*<<< orphan*/  address; } ;
struct atlas_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 scalar_t__ IIO_TEMP ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct atlas_data* iio_priv (struct iio_dev*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int atlas_write_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int val, int val2, long mask)
{
	struct atlas_data *data = iio_priv(indio_dev);
	__be32 reg = cpu_to_be32(val / 10);

	if (val2 != 0 || val < 0 || val > 20000)
		return -EINVAL;

	if (mask != IIO_CHAN_INFO_RAW || chan->type != IIO_TEMP)
		return -EINVAL;

	return regmap_bulk_write(data->regmap, chan->address,
				 &reg, sizeof(reg));
}