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
struct i2c_msg {int flags; int len; scalar_t__* buf; } ;
struct i2c_diolan_u2c {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int I2C_M_RD ; 
 int I2C_M_RECV_LEN ; 
 scalar_t__ I2C_SMBUS_BLOCK_MAX ; 
 int diolan_i2c_get_byte_ack (struct i2c_diolan_u2c*,int,scalar_t__*) ; 
 int diolan_i2c_put_byte_ack (struct i2c_diolan_u2c*,scalar_t__) ; 
 int diolan_i2c_repeated_start (struct i2c_diolan_u2c*) ; 
 int diolan_i2c_start (struct i2c_diolan_u2c*) ; 
 int diolan_i2c_stop (struct i2c_diolan_u2c*) ; 
 scalar_t__ i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 struct i2c_diolan_u2c* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int diolan_usb_xfer(struct i2c_adapter *adapter, struct i2c_msg *msgs,
			   int num)
{
	struct i2c_diolan_u2c *dev = i2c_get_adapdata(adapter);
	struct i2c_msg *pmsg;
	int i, j;
	int ret, sret;

	ret = diolan_i2c_start(dev);
	if (ret < 0)
		return ret;

	for (i = 0; i < num; i++) {
		pmsg = &msgs[i];
		if (i) {
			ret = diolan_i2c_repeated_start(dev);
			if (ret < 0)
				goto abort;
		}
		ret = diolan_i2c_put_byte_ack(dev,
					      i2c_8bit_addr_from_msg(pmsg));
		if (ret < 0)
			goto abort;
		if (pmsg->flags & I2C_M_RD) {
			for (j = 0; j < pmsg->len; j++) {
				u8 byte;
				bool ack = j < pmsg->len - 1;

				/*
				 * Don't send NACK if this is the first byte
				 * of a SMBUS_BLOCK message.
				 */
				if (j == 0 && (pmsg->flags & I2C_M_RECV_LEN))
					ack = true;

				ret = diolan_i2c_get_byte_ack(dev, ack, &byte);
				if (ret < 0)
					goto abort;
				/*
				 * Adjust count if first received byte is length
				 */
				if (j == 0 && (pmsg->flags & I2C_M_RECV_LEN)) {
					if (byte == 0
					    || byte > I2C_SMBUS_BLOCK_MAX) {
						ret = -EPROTO;
						goto abort;
					}
					pmsg->len += byte;
				}
				pmsg->buf[j] = byte;
			}
		} else {
			for (j = 0; j < pmsg->len; j++) {
				ret = diolan_i2c_put_byte_ack(dev,
							      pmsg->buf[j]);
				if (ret < 0)
					goto abort;
			}
		}
	}
	ret = num;
abort:
	sret = diolan_i2c_stop(dev);
	if (sret < 0 && ret >= 0)
		ret = sret;
	return ret;
}