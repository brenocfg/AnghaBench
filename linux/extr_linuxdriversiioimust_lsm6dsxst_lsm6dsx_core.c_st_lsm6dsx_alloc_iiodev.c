#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct st_lsm6dsx_sensor {int id; int watermark; int /*<<< orphan*/  name; int /*<<< orphan*/  gain; int /*<<< orphan*/  odr; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/ * info; void* num_channels; void* channels; int /*<<< orphan*/  available_scan_masks; TYPE_1__ dev; int /*<<< orphan*/  modes; } ;
typedef  enum st_lsm6dsx_sensor_id { ____Placeholder_st_lsm6dsx_sensor_id } st_lsm6dsx_sensor_id ;
struct TYPE_10__ {TYPE_3__* fs_avl; } ;
struct TYPE_9__ {TYPE_2__* odr_avl; } ;
struct TYPE_8__ {int /*<<< orphan*/  gain; } ;
struct TYPE_7__ {int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
#define  ST_LSM6DSX_ID_ACC 129 
#define  ST_LSM6DSX_ID_GYRO 128 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ ,int) ; 
 struct st_lsm6dsx_sensor* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 void* st_lsm6dsx_acc_channels ; 
 int /*<<< orphan*/  st_lsm6dsx_acc_info ; 
 int /*<<< orphan*/  st_lsm6dsx_available_scan_masks ; 
 TYPE_5__* st_lsm6dsx_fs_table ; 
 void* st_lsm6dsx_gyro_channels ; 
 int /*<<< orphan*/  st_lsm6dsx_gyro_info ; 
 TYPE_4__* st_lsm6dsx_odr_table ; 

__attribute__((used)) static struct iio_dev *st_lsm6dsx_alloc_iiodev(struct st_lsm6dsx_hw *hw,
					       enum st_lsm6dsx_sensor_id id,
					       const char *name)
{
	struct st_lsm6dsx_sensor *sensor;
	struct iio_dev *iio_dev;

	iio_dev = devm_iio_device_alloc(hw->dev, sizeof(*sensor));
	if (!iio_dev)
		return NULL;

	iio_dev->modes = INDIO_DIRECT_MODE;
	iio_dev->dev.parent = hw->dev;
	iio_dev->available_scan_masks = st_lsm6dsx_available_scan_masks;

	sensor = iio_priv(iio_dev);
	sensor->id = id;
	sensor->hw = hw;
	sensor->odr = st_lsm6dsx_odr_table[id].odr_avl[0].hz;
	sensor->gain = st_lsm6dsx_fs_table[id].fs_avl[0].gain;
	sensor->watermark = 1;

	switch (id) {
	case ST_LSM6DSX_ID_ACC:
		iio_dev->channels = st_lsm6dsx_acc_channels;
		iio_dev->num_channels = ARRAY_SIZE(st_lsm6dsx_acc_channels);
		iio_dev->info = &st_lsm6dsx_acc_info;

		scnprintf(sensor->name, sizeof(sensor->name), "%s_accel",
			  name);
		break;
	case ST_LSM6DSX_ID_GYRO:
		iio_dev->channels = st_lsm6dsx_gyro_channels;
		iio_dev->num_channels = ARRAY_SIZE(st_lsm6dsx_gyro_channels);
		iio_dev->info = &st_lsm6dsx_gyro_info;

		scnprintf(sensor->name, sizeof(sensor->name), "%s_gyro",
			  name);
		break;
	default:
		return NULL;
	}
	iio_dev->name = sensor->name;

	return iio_dev;
}