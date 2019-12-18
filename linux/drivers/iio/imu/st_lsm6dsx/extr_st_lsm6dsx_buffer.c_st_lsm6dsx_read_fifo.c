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
typedef  int u8 ;
typedef  int u16 ;
struct st_lsm6dsx_sensor {int sip; scalar_t__ ts_ref; } ;
struct st_lsm6dsx_hw {int sip; int ts_sip; int /*<<< orphan*/  dev; int /*<<< orphan*/ * iio_devs; int /*<<< orphan*/ * buff; TYPE_3__* settings; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  fifo_status ;
typedef  int /*<<< orphan*/  data ;
typedef  int __le16 ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ fifo_diff; } ;
struct TYPE_6__ {TYPE_2__ fifo_ops; } ;

/* Variables and functions */
 int ST_LSM6DSX_CHAN_SIZE ; 
 int /*<<< orphan*/  ST_LSM6DSX_FIFO_EMPTY_MASK ; 
 size_t ST_LSM6DSX_ID_ACC ; 
 size_t ST_LSM6DSX_ID_GYRO ; 
 int ST_LSM6DSX_IIO_BUFF_SIZE ; 
 int /*<<< orphan*/  ST_LSM6DSX_MAX_WORD_LEN ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_FIFO_OUTL_ADDR ; 
 int ST_LSM6DSX_SAMPLE_SIZE ; 
 int ST_LSM6DSX_TS_SENSITIVITY ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int st_lsm6dsx_read_block (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_read_locked (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int*,int) ; 
 int st_lsm6dsx_reset_hw_ts (struct st_lsm6dsx_hw*) ; 
 scalar_t__ unlikely (int) ; 

int st_lsm6dsx_read_fifo(struct st_lsm6dsx_hw *hw)
{
	u16 fifo_len, pattern_len = hw->sip * ST_LSM6DSX_SAMPLE_SIZE;
	u16 fifo_diff_mask = hw->settings->fifo_ops.fifo_diff.mask;
	int err, acc_sip, gyro_sip, ts_sip, read_len, offset;
	struct st_lsm6dsx_sensor *acc_sensor, *gyro_sensor;
	u8 gyro_buff[ST_LSM6DSX_IIO_BUFF_SIZE];
	u8 acc_buff[ST_LSM6DSX_IIO_BUFF_SIZE];
	bool reset_ts = false;
	__le16 fifo_status;
	s64 ts = 0;

	err = st_lsm6dsx_read_locked(hw,
				     hw->settings->fifo_ops.fifo_diff.addr,
				     &fifo_status, sizeof(fifo_status));
	if (err < 0) {
		dev_err(hw->dev, "failed to read fifo status (err=%d)\n",
			err);
		return err;
	}

	if (fifo_status & cpu_to_le16(ST_LSM6DSX_FIFO_EMPTY_MASK))
		return 0;

	fifo_len = (le16_to_cpu(fifo_status) & fifo_diff_mask) *
		   ST_LSM6DSX_CHAN_SIZE;
	fifo_len = (fifo_len / pattern_len) * pattern_len;

	acc_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
	gyro_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_GYRO]);

	for (read_len = 0; read_len < fifo_len; read_len += pattern_len) {
		err = st_lsm6dsx_read_block(hw, ST_LSM6DSX_REG_FIFO_OUTL_ADDR,
					    hw->buff, pattern_len,
					    ST_LSM6DSX_MAX_WORD_LEN);
		if (err < 0) {
			dev_err(hw->dev,
				"failed to read pattern from fifo (err=%d)\n",
				err);
			return err;
		}

		/*
		 * Data are written to the FIFO with a specific pattern
		 * depending on the configured ODRs. The first sequence of data
		 * stored in FIFO contains the data of all enabled sensors
		 * (e.g. Gx, Gy, Gz, Ax, Ay, Az, Ts), then data are repeated
		 * depending on the value of the decimation factor set for each
		 * sensor.
		 *
		 * Supposing the FIFO is storing data from gyroscope and
		 * accelerometer at different ODRs:
		 *   - gyroscope ODR = 208Hz, accelerometer ODR = 104Hz
		 * Since the gyroscope ODR is twice the accelerometer one, the
		 * following pattern is repeated every 9 samples:
		 *   - Gx, Gy, Gz, Ax, Ay, Az, Ts, Gx, Gy, Gz, Ts, Gx, ..
		 */
		gyro_sip = gyro_sensor->sip;
		acc_sip = acc_sensor->sip;
		ts_sip = hw->ts_sip;
		offset = 0;

		while (acc_sip > 0 || gyro_sip > 0) {
			if (gyro_sip > 0) {
				memcpy(gyro_buff, &hw->buff[offset],
				       ST_LSM6DSX_SAMPLE_SIZE);
				offset += ST_LSM6DSX_SAMPLE_SIZE;
			}
			if (acc_sip > 0) {
				memcpy(acc_buff, &hw->buff[offset],
				       ST_LSM6DSX_SAMPLE_SIZE);
				offset += ST_LSM6DSX_SAMPLE_SIZE;
			}

			if (ts_sip-- > 0) {
				u8 data[ST_LSM6DSX_SAMPLE_SIZE];

				memcpy(data, &hw->buff[offset], sizeof(data));
				/*
				 * hw timestamp is 3B long and it is stored
				 * in FIFO using 6B as 4th FIFO data set
				 * according to this schema:
				 * B0 = ts[15:8], B1 = ts[23:16], B3 = ts[7:0]
				 */
				ts = data[1] << 16 | data[0] << 8 | data[3];
				/*
				 * check if hw timestamp engine is going to
				 * reset (the sensor generates an interrupt
				 * to signal the hw timestamp will reset in
				 * 1.638s)
				 */
				if (!reset_ts && ts >= 0xff0000)
					reset_ts = true;
				ts *= ST_LSM6DSX_TS_SENSITIVITY;

				offset += ST_LSM6DSX_SAMPLE_SIZE;
			}

			if (gyro_sip-- > 0)
				iio_push_to_buffers_with_timestamp(
					hw->iio_devs[ST_LSM6DSX_ID_GYRO],
					gyro_buff, gyro_sensor->ts_ref + ts);
			if (acc_sip-- > 0)
				iio_push_to_buffers_with_timestamp(
					hw->iio_devs[ST_LSM6DSX_ID_ACC],
					acc_buff, acc_sensor->ts_ref + ts);
		}
	}

	if (unlikely(reset_ts)) {
		err = st_lsm6dsx_reset_hw_ts(hw);
		if (err < 0) {
			dev_err(hw->dev, "failed to reset hw ts (err=%d)\n",
				err);
			return err;
		}
	}
	return read_len;
}