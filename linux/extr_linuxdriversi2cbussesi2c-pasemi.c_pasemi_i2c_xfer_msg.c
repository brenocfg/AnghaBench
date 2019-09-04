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
typedef  int u32 ;
struct pasemi_smbus {int dummy; } ;
struct i2c_msg {int flags; int len; int* buf; } ;
struct i2c_adapter {struct pasemi_smbus* algo_data; } ;

/* Variables and functions */
 int CLK_100K_DIV ; 
 int CTL_CLK_M ; 
 int CTL_MRR ; 
 int CTL_MTR ; 
 int ENODATA ; 
 int I2C_M_RD ; 
 int MRXFIFO_DATA_M ; 
 int MRXFIFO_EMPTY ; 
 int MTXFIFO_READ ; 
 int MTXFIFO_START ; 
 int MTXFIFO_STOP ; 
 int /*<<< orphan*/  REG_CTL ; 
 int RXFIFO_RD (struct pasemi_smbus*) ; 
 int /*<<< orphan*/  TXFIFO_WR (struct pasemi_smbus*,int) ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int pasemi_smb_waitready (struct pasemi_smbus*) ; 
 int /*<<< orphan*/  reg_write (struct pasemi_smbus*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pasemi_i2c_xfer_msg(struct i2c_adapter *adapter,
			       struct i2c_msg *msg, int stop)
{
	struct pasemi_smbus *smbus = adapter->algo_data;
	int read, i, err;
	u32 rd;

	read = msg->flags & I2C_M_RD ? 1 : 0;

	TXFIFO_WR(smbus, MTXFIFO_START | i2c_8bit_addr_from_msg(msg));

	if (read) {
		TXFIFO_WR(smbus, msg->len | MTXFIFO_READ |
				 (stop ? MTXFIFO_STOP : 0));

		err = pasemi_smb_waitready(smbus);
		if (err)
			goto reset_out;

		for (i = 0; i < msg->len; i++) {
			rd = RXFIFO_RD(smbus);
			if (rd & MRXFIFO_EMPTY) {
				err = -ENODATA;
				goto reset_out;
			}
			msg->buf[i] = rd & MRXFIFO_DATA_M;
		}
	} else {
		for (i = 0; i < msg->len - 1; i++)
			TXFIFO_WR(smbus, msg->buf[i]);

		TXFIFO_WR(smbus, msg->buf[msg->len-1] |
			  (stop ? MTXFIFO_STOP : 0));
	}

	return 0;

 reset_out:
	reg_write(smbus, REG_CTL, (CTL_MTR | CTL_MRR |
		  (CLK_100K_DIV & CTL_CLK_M)));
	return err;
}