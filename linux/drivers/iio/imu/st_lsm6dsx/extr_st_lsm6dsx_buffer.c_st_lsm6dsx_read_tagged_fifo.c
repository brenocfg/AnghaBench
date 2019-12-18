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
struct st_lsm6dsx_hw {int sip; int* buff; int /*<<< orphan*/  dev; TYPE_3__* settings; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  fifo_status ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ fifo_diff; } ;
struct TYPE_6__ {TYPE_2__ fifo_ops; } ;

/* Variables and functions */
 int ST_LSM6DSX_IIO_BUFF_SIZE ; 
 int /*<<< orphan*/  ST_LSM6DSX_MAX_TAGGED_WORD_LEN ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_FIFO_OUT_TAG_ADDR ; 
 int /*<<< orphan*/  ST_LSM6DSX_SAMPLE_SIZE ; 
 int ST_LSM6DSX_TAGGED_SAMPLE_SIZE ; 
 int ST_LSM6DSX_TAG_SIZE ; 
 int ST_LSM6DSX_TS_SENSITIVITY ; 
 int ST_LSM6DSX_TS_TAG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_lsm6dsx_push_tagged_data (struct st_lsm6dsx_hw*,int,int*,int) ; 
 int st_lsm6dsx_read_block (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_read_locked (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int st_lsm6dsx_reset_hw_ts (struct st_lsm6dsx_hw*) ; 
 scalar_t__ unlikely (int) ; 

int st_lsm6dsx_read_tagged_fifo(struct st_lsm6dsx_hw *hw)
{
	u16 pattern_len = hw->sip * ST_LSM6DSX_TAGGED_SAMPLE_SIZE;
	u16 fifo_len, fifo_diff_mask;
	u8 iio_buff[ST_LSM6DSX_IIO_BUFF_SIZE], tag;
	bool reset_ts = false;
	int i, err, read_len;
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

	fifo_diff_mask = hw->settings->fifo_ops.fifo_diff.mask;
	fifo_len = (le16_to_cpu(fifo_status) & fifo_diff_mask) *
		   ST_LSM6DSX_TAGGED_SAMPLE_SIZE;
	if (!fifo_len)
		return 0;

	for (read_len = 0; read_len < fifo_len; read_len += pattern_len) {
		err = st_lsm6dsx_read_block(hw,
					    ST_LSM6DSX_REG_FIFO_OUT_TAG_ADDR,
					    hw->buff, pattern_len,
					    ST_LSM6DSX_MAX_TAGGED_WORD_LEN);
		if (err < 0) {
			dev_err(hw->dev,
				"failed to read pattern from fifo (err=%d)\n",
				err);
			return err;
		}

		for (i = 0; i < pattern_len;
		     i += ST_LSM6DSX_TAGGED_SAMPLE_SIZE) {
			memcpy(iio_buff, &hw->buff[i + ST_LSM6DSX_TAG_SIZE],
			       ST_LSM6DSX_SAMPLE_SIZE);

			tag = hw->buff[i] >> 3;
			if (tag == ST_LSM6DSX_TS_TAG) {
				/*
				 * hw timestamp is 4B long and it is stored
				 * in FIFO according to this schema:
				 * B0 = ts[7:0], B1 = ts[15:8], B2 = ts[23:16],
				 * B3 = ts[31:24]
				 */
				ts = le32_to_cpu(*((__le32 *)iio_buff));
				/*
				 * check if hw timestamp engine is going to
				 * reset (the sensor generates an interrupt
				 * to signal the hw timestamp will reset in
				 * 1.638s)
				 */
				if (!reset_ts && ts >= 0xffff0000)
					reset_ts = true;
				ts *= ST_LSM6DSX_TS_SENSITIVITY;
			} else {
				st_lsm6dsx_push_tagged_data(hw, tag, iio_buff,
							    ts);
			}
		}
	}

	if (unlikely(reset_ts)) {
		err = st_lsm6dsx_reset_hw_ts(hw);
		if (err < 0)
			return err;
	}
	return read_len;
}