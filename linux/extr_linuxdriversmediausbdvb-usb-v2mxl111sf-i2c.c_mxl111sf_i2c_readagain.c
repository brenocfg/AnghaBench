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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ mxl111sf_i2c_check_fifo (struct mxl111sf_state*) ; 
 int mxl111sf_i2c_check_status (struct mxl111sf_state*) ; 
 int /*<<< orphan*/  mxl111sf_i2c_get_data (struct mxl111sf_state*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mxl_i2c (char*,...) ; 

__attribute__((used)) static int mxl111sf_i2c_readagain(struct mxl111sf_state *state,
				  u8 count, u8 *rbuf)
{
	u8 i2c_w_data[26];
	u8 i2c_r_data[24];
	u8 i = 0;
	u8 fifo_status = 0;
	int status = 0;

	mxl_i2c("read %d bytes", count);

	while ((fifo_status == 0) && (i++ < 5))
		fifo_status = mxl111sf_i2c_check_fifo(state);

	i2c_w_data[0] = 0xDD;
	i2c_w_data[1] = 0x00;

	for (i = 2; i < 26; i++)
		i2c_w_data[i] = 0xFE;

	for (i = 0; i < count; i++) {
		i2c_w_data[2+(i*3)] = 0x0C;
		i2c_w_data[3+(i*3)] = 0x00;
		i2c_w_data[4+(i*3)] = 0x00;
	}

	mxl111sf_i2c_get_data(state, 0, i2c_w_data, i2c_r_data);

	/* Check for I2C NACK status */
	if (mxl111sf_i2c_check_status(state) == 1) {
		mxl_i2c("error!");
	} else {
		for (i = 0; i < count; i++) {
			rbuf[i] = i2c_r_data[(i*3)+1];
			mxl_i2c("%02x\t %02x",
				i2c_r_data[(i*3)+1],
				i2c_r_data[(i*3)+2]);
		}

		status = 1;
	}

	return status;
}