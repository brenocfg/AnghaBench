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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_msg {int* buf; int len; scalar_t__ addr; } ;
struct dibx000_i2c_master {scalar_t__ base_reg; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ dibx000_is_i2c_done (struct dibx000_i2c_master*) ; 
 int dibx000_read_word (struct dibx000_i2c_master*,scalar_t__) ; 
 int /*<<< orphan*/  dibx000_write_word (struct dibx000_i2c_master*,scalar_t__,int) ; 

__attribute__((used)) static int dibx000_master_i2c_read(struct dibx000_i2c_master *mst, struct i2c_msg *msg)
{
	u16 da;
	u8 *b = msg->buf;
	u16 rxlen = msg->len, len;

	while (rxlen) {
		len = rxlen > 8 ? 8 : rxlen;
		da = (((u8) (msg->addr)) << 9) |
			(1           << 8) |
			(1           << 7) |
			(0           << 6) |
			(0           << 5) |
			((len & 0x7) << 2) |
			(1           << 1) |
			(0           << 0);

		if (rxlen == msg->len)
			da |= 1 << 5; /* start */

		if (rxlen-len == 0)
			da |= 1 << 6; /* stop */
		dibx000_write_word(mst, mst->base_reg+1, da);

		if (dibx000_is_i2c_done(mst) != 0)
			return -EREMOTEIO;

		rxlen -= len;

		while (len) {
			da = dibx000_read_word(mst, mst->base_reg);
			*b++ = (da >> 8) & 0xff;
			len--;
			if (len >= 1) {
				*b++ =  da   & 0xff;
				len--;
			}
		}
	}

	return 0;
}