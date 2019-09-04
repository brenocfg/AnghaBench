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
typedef  int u16 ;
struct kxsd9_state {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  raw_val ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 unsigned int KXSD9_CTRL_C_FS_MASK ; 
 int /*<<< orphan*/  KXSD9_REG_CTRL_C ; 
 int KXSD9_ZERO_G_OFFSET ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct kxsd9_state* iio_priv (struct iio_dev*) ; 
 int* kxsd9_micro_scales ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int kxsd9_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan,
			  int *val, int *val2, long mask)
{
	int ret = -EINVAL;
	struct kxsd9_state *st = iio_priv(indio_dev);
	unsigned int regval;
	__be16 raw_val;
	u16 nval;

	pm_runtime_get_sync(st->dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = regmap_bulk_read(st->map, chan->address, &raw_val,
				       sizeof(raw_val));
		if (ret)
			goto error_ret;
		nval = be16_to_cpu(raw_val);
		/* Only 12 bits are valid */
		nval >>= 4;
		*val = nval;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_OFFSET:
		/* This has a bias of -2048 */
		*val = KXSD9_ZERO_G_OFFSET;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		ret = regmap_read(st->map,
				  KXSD9_REG_CTRL_C,
				  &regval);
		if (ret < 0)
			goto error_ret;
		*val = 0;
		*val2 = kxsd9_micro_scales[regval & KXSD9_CTRL_C_FS_MASK];
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	}

error_ret:
	pm_runtime_mark_last_busy(st->dev);
	pm_runtime_put_autosuspend(st->dev);

	return ret;
}