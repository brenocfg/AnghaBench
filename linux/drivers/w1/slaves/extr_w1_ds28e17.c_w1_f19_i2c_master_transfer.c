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
struct w1_slave {TYPE_1__* master; } ;
struct i2c_msg {scalar_t__ addr; int flags; scalar_t__ len; scalar_t__* buf; } ;
struct i2c_adapter {scalar_t__ algo_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EIO ; 
 int I2C_M_RD ; 
 int I2C_M_RECV_LEN ; 
 scalar_t__ W1_F19_WRITE_DATA_LIMIT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_f19_i2c_read (struct w1_slave*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int w1_f19_i2c_write (struct w1_slave*,scalar_t__,scalar_t__*,scalar_t__,int) ; 
 int w1_f19_i2c_write_read (struct w1_slave*,scalar_t__,scalar_t__*,scalar_t__,scalar_t__*,scalar_t__) ; 
 scalar_t__ w1_reset_resume_command (TYPE_1__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 

__attribute__((used)) static int w1_f19_i2c_master_transfer(struct i2c_adapter *adapter,
	struct i2c_msg *msgs, int num)
{
	struct w1_slave *sl = (struct w1_slave *) adapter->algo_data;
	int i = 0;
	int result = 0;

	/* Start onewire transaction. */
	mutex_lock(&sl->master->bus_mutex);

	/* Select DS28E17. */
	if (w1_reset_select_slave(sl)) {
		i = -EIO;
		goto error;
	}

	/* Loop while there are still messages to transfer. */
	while (i < num) {
		/*
		 * Check for special case: Small write followed
		 * by read to same I2C device.
		 */
		if (i < (num-1)
			&& msgs[i].addr == msgs[i+1].addr
			&& !(msgs[i].flags & I2C_M_RD)
			&& (msgs[i+1].flags & I2C_M_RD)
			&& (msgs[i].len <= W1_F19_WRITE_DATA_LIMIT)) {
			/*
			 * The DS28E17 has a combined transfer
			 * for small write+read.
			 */
			result = w1_f19_i2c_write_read(sl, msgs[i].addr,
				msgs[i].buf, msgs[i].len,
				msgs[i+1].buf, msgs[i+1].len);
			if (result < 0) {
				i = result;
				goto error;
			}

			/*
			 * Check if we should interpret the read data
			 * as a length byte. The DS28E17 unfortunately
			 * has no read without stop, so we can just do
			 * another simple read in that case.
			 */
			if (msgs[i+1].flags & I2C_M_RECV_LEN) {
				result = w1_f19_i2c_read(sl, msgs[i+1].addr,
					&(msgs[i+1].buf[1]), msgs[i+1].buf[0]);
				if (result < 0) {
					i = result;
					goto error;
				}
			}

			/* Eat up read message, too. */
			i++;
		} else if (msgs[i].flags & I2C_M_RD) {
			/* Read transfer. */
			result = w1_f19_i2c_read(sl, msgs[i].addr,
				msgs[i].buf, msgs[i].len);
			if (result < 0) {
				i = result;
				goto error;
			}

			/*
			 * Check if we should interpret the read data
			 * as a length byte. The DS28E17 unfortunately
			 * has no read without stop, so we can just do
			 * another simple read in that case.
			 */
			if (msgs[i].flags & I2C_M_RECV_LEN) {
				result = w1_f19_i2c_read(sl,
					msgs[i].addr,
					&(msgs[i].buf[1]),
					msgs[i].buf[0]);
				if (result < 0) {
					i = result;
					goto error;
				}
			}
		} else {
			/*
			 * Write transfer.
			 * Stop condition only for last
			 * transfer.
			 */
			result = w1_f19_i2c_write(sl,
				msgs[i].addr,
				msgs[i].buf,
				msgs[i].len,
				i == (num-1));
			if (result < 0) {
				i = result;
				goto error;
			}
		}

		/* Next message. */
		i++;

		/* Are there still messages to send/receive? */
		if (i < num) {
			/* Yes. Resume to same DS28E17. */
			if (w1_reset_resume_command(sl->master)) {
				i = -EIO;
				goto error;
			}
		}
	}

error:
	/* End onewire transaction. */
	mutex_unlock(&sl->master->bus_mutex);

	/* Return number of messages processed or error. */
	return i;
}