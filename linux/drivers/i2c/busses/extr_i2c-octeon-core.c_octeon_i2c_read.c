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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct octeon_i2c {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ I2C_SMBUS_BLOCK_MAX ; 
 int TWSI_CTL_AAK ; 
 int TWSI_CTL_ENAB ; 
 int octeon_i2c_check_status (struct octeon_i2c*,int) ; 
 int /*<<< orphan*/  octeon_i2c_ctl_write (struct octeon_i2c*,int) ; 
 scalar_t__ octeon_i2c_data_read (struct octeon_i2c*,int*) ; 
 int /*<<< orphan*/  octeon_i2c_data_write (struct octeon_i2c*,int) ; 
 int octeon_i2c_wait (struct octeon_i2c*) ; 

__attribute__((used)) static int octeon_i2c_read(struct octeon_i2c *i2c, int target,
			   u8 *data, u16 *rlength, bool recv_len)
{
	int i, result, length = *rlength;
	bool final_read = false;

	octeon_i2c_data_write(i2c, (target << 1) | 1);
	octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB);

	result = octeon_i2c_wait(i2c);
	if (result)
		return result;

	/* address OK ? */
	result = octeon_i2c_check_status(i2c, false);
	if (result)
		return result;

	for (i = 0; i < length; i++) {
		/*
		 * For the last byte to receive TWSI_CTL_AAK must not be set.
		 *
		 * A special case is I2C_M_RECV_LEN where we don't know the
		 * additional length yet. If recv_len is set we assume we're
		 * not reading the final byte and therefore need to set
		 * TWSI_CTL_AAK.
		 */
		if ((i + 1 == length) && !(recv_len && i == 0))
			final_read = true;

		/* clear iflg to allow next event */
		if (final_read)
			octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB);
		else
			octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB | TWSI_CTL_AAK);

		result = octeon_i2c_wait(i2c);
		if (result)
			return result;

		data[i] = octeon_i2c_data_read(i2c, &result);
		if (result)
			return result;
		if (recv_len && i == 0) {
			if (data[i] > I2C_SMBUS_BLOCK_MAX + 1)
				return -EPROTO;
			length += data[i];
		}

		result = octeon_i2c_check_status(i2c, final_read);
		if (result)
			return result;
	}
	*rlength = length;
	return 0;
}