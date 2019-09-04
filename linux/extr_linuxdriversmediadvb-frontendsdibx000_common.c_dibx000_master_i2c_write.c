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
struct i2c_msg {int len; int* buf; scalar_t__ addr; } ;
struct dibx000_i2c_master {scalar_t__ base_reg; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ dibx000_is_i2c_done (struct dibx000_i2c_master*) ; 
 int /*<<< orphan*/  dibx000_read_word (struct dibx000_i2c_master*,scalar_t__) ; 
 int /*<<< orphan*/  dibx000_write_word (struct dibx000_i2c_master*,scalar_t__,int) ; 

__attribute__((used)) static int dibx000_master_i2c_write(struct dibx000_i2c_master *mst, struct i2c_msg *msg, u8 stop)
{
	u16 data;
	u16 da;
	u16 i;
	u16 txlen = msg->len, len;
	const u8 *b = msg->buf;

	while (txlen) {
		dibx000_read_word(mst, mst->base_reg + 2);

		len = txlen > 8 ? 8 : txlen;
		for (i = 0; i < len; i += 2) {
			data = *b++ << 8;
			if (i+1 < len)
				data |= *b++;
			dibx000_write_word(mst, mst->base_reg, data);
		}
		da = (((u8) (msg->addr))  << 9) |
			(1           << 8) |
			(1           << 7) |
			(0           << 6) |
			(0           << 5) |
			((len & 0x7) << 2) |
			(0           << 1) |
			(0           << 0);

		if (txlen == msg->len)
			da |= 1 << 5; /* start */

		if (txlen-len == 0 && stop)
			da |= 1 << 6; /* stop */

		dibx000_write_word(mst, mst->base_reg+1, da);

		if (dibx000_is_i2c_done(mst) != 0)
			return -EREMOTEIO;
		txlen -= len;
	}

	return 0;
}