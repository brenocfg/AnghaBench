#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_13__ {int /*<<< orphan*/  addr; struct st_lsm6dsx_ext_dev_settings const* settings; } ;
struct st_lsm6dsx_sensor {int id; int watermark; int /*<<< orphan*/  name; TYPE_6__ ext_info; int /*<<< orphan*/  gain; int /*<<< orphan*/  odr; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {TYPE_4__* fs_avl; } ;
struct TYPE_10__ {TYPE_2__* odr_avl; } ;
struct st_lsm6dsx_ext_dev_settings {int id; TYPE_7__ out; TYPE_5__ fs_table; TYPE_3__ odr_table; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; struct iio_chan_spec* channels; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  modes; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int /*<<< orphan*/  magn_channels ;
typedef  enum st_lsm6dsx_sensor_id { ____Placeholder_st_lsm6dsx_sensor_id } st_lsm6dsx_sensor_id ;
struct TYPE_11__ {int /*<<< orphan*/  gain; } ;
struct TYPE_9__ {int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct iio_chan_spec const*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iio_chan_spec const IIO_CHAN_SOFT_TIMESTAMP (int) ; 
 int /*<<< orphan*/  IIO_MAGN ; 
 int /*<<< orphan*/  IIO_MOD_X ; 
 int /*<<< orphan*/  IIO_MOD_Y ; 
 int /*<<< orphan*/  IIO_MOD_Z ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 struct iio_chan_spec const ST_LSM6DSX_CHANNEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  ST_LSM6DSX_ID_MAGN 128 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ ,int) ; 
 struct iio_chan_spec* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct st_lsm6dsx_sensor* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  memcpy (struct iio_chan_spec*,struct iio_chan_spec const*,int) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  st_lsm6dsx_available_scan_masks ; 
 int /*<<< orphan*/  st_lsm6dsx_ext_info ; 

__attribute__((used)) static struct iio_dev *
st_lsm6dsx_shub_alloc_iiodev(struct st_lsm6dsx_hw *hw,
			     enum st_lsm6dsx_sensor_id id,
			     const struct st_lsm6dsx_ext_dev_settings *info,
			     u8 i2c_addr, const char *name)
{
	struct iio_chan_spec *ext_channels;
	struct st_lsm6dsx_sensor *sensor;
	struct iio_dev *iio_dev;

	iio_dev = devm_iio_device_alloc(hw->dev, sizeof(*sensor));
	if (!iio_dev)
		return NULL;

	iio_dev->modes = INDIO_DIRECT_MODE;
	iio_dev->dev.parent = hw->dev;
	iio_dev->info = &st_lsm6dsx_ext_info;

	sensor = iio_priv(iio_dev);
	sensor->id = id;
	sensor->hw = hw;
	sensor->odr = info->odr_table.odr_avl[0].hz;
	sensor->gain = info->fs_table.fs_avl[0].gain;
	sensor->ext_info.settings = info;
	sensor->ext_info.addr = i2c_addr;
	sensor->watermark = 1;

	switch (info->id) {
	case ST_LSM6DSX_ID_MAGN: {
		const struct iio_chan_spec magn_channels[] = {
			ST_LSM6DSX_CHANNEL(IIO_MAGN, info->out.addr,
					   IIO_MOD_X, 0),
			ST_LSM6DSX_CHANNEL(IIO_MAGN, info->out.addr + 2,
					   IIO_MOD_Y, 1),
			ST_LSM6DSX_CHANNEL(IIO_MAGN, info->out.addr + 4,
					   IIO_MOD_Z, 2),
			IIO_CHAN_SOFT_TIMESTAMP(3),
		};

		ext_channels = devm_kzalloc(hw->dev, sizeof(magn_channels),
					    GFP_KERNEL);
		if (!ext_channels)
			return NULL;

		memcpy(ext_channels, magn_channels, sizeof(magn_channels));
		iio_dev->available_scan_masks = st_lsm6dsx_available_scan_masks;
		iio_dev->channels = ext_channels;
		iio_dev->num_channels = ARRAY_SIZE(magn_channels);

		scnprintf(sensor->name, sizeof(sensor->name), "%s_magn",
			  name);
		break;
	}
	default:
		return NULL;
	}
	iio_dev->name = sensor->name;

	return iio_dev;
}