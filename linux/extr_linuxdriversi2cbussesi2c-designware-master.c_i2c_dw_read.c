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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct i2c_msg {int flags; scalar_t__ len; void** buf; } ;
struct dw_i2c_dev {size_t msg_read_idx; size_t msgs_num; int status; scalar_t__ rx_buf_len; void** rx_buf; int /*<<< orphan*/  rx_outstanding; struct i2c_msg* msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_DATA_CMD ; 
 int /*<<< orphan*/  DW_IC_RXFLR ; 
 int I2C_M_RD ; 
 scalar_t__ I2C_M_RECV_LEN ; 
 void* I2C_SMBUS_BLOCK_MAX ; 
 int STATUS_READ_IN_PROGRESS ; 
 void* dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_dw_recv_len (struct dw_i2c_dev*,void*) ; 

__attribute__((used)) static void
i2c_dw_read(struct dw_i2c_dev *dev)
{
	struct i2c_msg *msgs = dev->msgs;
	int rx_valid;

	for (; dev->msg_read_idx < dev->msgs_num; dev->msg_read_idx++) {
		u32 len;
		u8 *buf;

		if (!(msgs[dev->msg_read_idx].flags & I2C_M_RD))
			continue;

		if (!(dev->status & STATUS_READ_IN_PROGRESS)) {
			len = msgs[dev->msg_read_idx].len;
			buf = msgs[dev->msg_read_idx].buf;
		} else {
			len = dev->rx_buf_len;
			buf = dev->rx_buf;
		}

		rx_valid = dw_readl(dev, DW_IC_RXFLR);

		for (; len > 0 && rx_valid > 0; len--, rx_valid--) {
			u32 flags = msgs[dev->msg_read_idx].flags;

			*buf = dw_readl(dev, DW_IC_DATA_CMD);
			/* Ensure length byte is a valid value */
			if (flags & I2C_M_RECV_LEN &&
				*buf <= I2C_SMBUS_BLOCK_MAX && *buf > 0) {
				len = i2c_dw_recv_len(dev, *buf);
			}
			buf++;
			dev->rx_outstanding--;
		}

		if (len > 0) {
			dev->status |= STATUS_READ_IN_PROGRESS;
			dev->rx_buf_len = len;
			dev->rx_buf = buf;
			return;
		} else
			dev->status &= ~STATUS_READ_IN_PROGRESS;
	}
}