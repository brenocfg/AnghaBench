#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct TYPE_4__ {int accl_fifo_enable; int gyro_fifo_enable; } ;
struct inv_mpu6050_state {scalar_t__ chip_type; int /*<<< orphan*/  lock; scalar_t__ skip_samples; TYPE_3__* reg; int /*<<< orphan*/  map; TYPE_2__* hw; TYPE_1__ chip_config; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  fifo_r_w; int /*<<< orphan*/  fifo_count_h; int /*<<< orphan*/  int_status; } ;
struct TYPE_5__ {size_t fifo_size; } ;

/* Variables and functions */
 scalar_t__ INV_ICM20602 ; 
 scalar_t__ INV_ICM20602_BYTES_PER_TEMP_SENSOR ; 
 int INV_MPU6050_BIT_RAW_DATA_RDY_INT ; 
 scalar_t__ INV_MPU6050_BYTES_PER_3AXIS_SENSOR ; 
 size_t INV_MPU6050_FIFO_COUNT_BYTE ; 
 int INV_MPU6050_OUTPUT_DATA_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 size_t get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inv_mpu6050_get_timestamp (struct inv_mpu6050_state*) ; 
 int /*<<< orphan*/  inv_mpu6050_update_period (struct inv_mpu6050_state*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  inv_reset_fifo (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

irqreturn_t inv_mpu6050_read_fifo(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct inv_mpu6050_state *st = iio_priv(indio_dev);
	size_t bytes_per_datum;
	int result;
	u8 data[INV_MPU6050_OUTPUT_DATA_SIZE];
	u16 fifo_count;
	s64 timestamp;
	int int_status;
	size_t i, nb;

	mutex_lock(&st->lock);

	/* ack interrupt and check status */
	result = regmap_read(st->map, st->reg->int_status, &int_status);
	if (result) {
		dev_err(regmap_get_device(st->map),
			"failed to ack interrupt\n");
		goto flush_fifo;
	}
	if (!(int_status & INV_MPU6050_BIT_RAW_DATA_RDY_INT)) {
		dev_warn(regmap_get_device(st->map),
			"spurious interrupt with status 0x%x\n", int_status);
		goto end_session;
	}

	if (!(st->chip_config.accl_fifo_enable |
		st->chip_config.gyro_fifo_enable))
		goto end_session;
	bytes_per_datum = 0;
	if (st->chip_config.accl_fifo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	if (st->chip_config.gyro_fifo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	if (st->chip_type == INV_ICM20602)
		bytes_per_datum += INV_ICM20602_BYTES_PER_TEMP_SENSOR;

	/*
	 * read fifo_count register to know how many bytes are inside the FIFO
	 * right now
	 */
	result = regmap_bulk_read(st->map, st->reg->fifo_count_h, data,
				  INV_MPU6050_FIFO_COUNT_BYTE);
	if (result)
		goto end_session;
	fifo_count = get_unaligned_be16(&data[0]);

	/*
	 * Handle fifo overflow by resetting fifo.
	 * Reset if there is only 3 data set free remaining to mitigate
	 * possible delay between reading fifo count and fifo data.
	 */
	nb = 3 * bytes_per_datum;
	if (fifo_count >= st->hw->fifo_size - nb) {
		dev_warn(regmap_get_device(st->map), "fifo overflow reset\n");
		goto flush_fifo;
	}

	/* compute and process all complete datum */
	nb = fifo_count / bytes_per_datum;
	inv_mpu6050_update_period(st, pf->timestamp, nb);
	for (i = 0; i < nb; ++i) {
		result = regmap_bulk_read(st->map, st->reg->fifo_r_w,
					  data, bytes_per_datum);
		if (result)
			goto flush_fifo;
		/* skip first samples if needed */
		if (st->skip_samples) {
			st->skip_samples--;
			continue;
		}
		timestamp = inv_mpu6050_get_timestamp(st);
		iio_push_to_buffers_with_timestamp(indio_dev, data, timestamp);
	}

end_session:
	mutex_unlock(&st->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;

flush_fifo:
	/* Flush HW and SW FIFOs. */
	inv_reset_fifo(indio_dev);
	mutex_unlock(&st->lock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}