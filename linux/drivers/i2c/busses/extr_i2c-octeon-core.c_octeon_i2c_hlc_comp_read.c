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
typedef  int u64 ;
struct octeon_i2c {scalar_t__ twsi_base; } ;
struct i2c_msg {int len; int addr; int flags; int* buf; } ;

/* Variables and functions */
 int I2C_M_TEN ; 
 scalar_t__ SW_TWSI (struct octeon_i2c*) ; 
 int SW_TWSI_ADDR_SHIFT ; 
 int SW_TWSI_EIA ; 
 scalar_t__ SW_TWSI_EXT (struct octeon_i2c*) ; 
 int SW_TWSI_IA_SHIFT ; 
 int SW_TWSI_OP_10_IA ; 
 int SW_TWSI_OP_7_IA ; 
 int SW_TWSI_R ; 
 int SW_TWSI_SIZE_SHIFT ; 
 int SW_TWSI_SOVR ; 
 int SW_TWSI_V ; 
 int __raw_readq (scalar_t__) ; 
 int octeon_i2c_check_status (struct octeon_i2c*,int) ; 
 int /*<<< orphan*/  octeon_i2c_hlc_enable (struct octeon_i2c*) ; 
 int /*<<< orphan*/  octeon_i2c_hlc_int_clear (struct octeon_i2c*) ; 
 int octeon_i2c_hlc_wait (struct octeon_i2c*) ; 
 int /*<<< orphan*/  octeon_i2c_writeq_flush (int,scalar_t__) ; 

__attribute__((used)) static int octeon_i2c_hlc_comp_read(struct octeon_i2c *i2c, struct i2c_msg *msgs)
{
	int i, j, ret = 0;
	u64 cmd;

	octeon_i2c_hlc_enable(i2c);

	cmd = SW_TWSI_V | SW_TWSI_R | SW_TWSI_SOVR;
	/* SIZE */
	cmd |= (u64)(msgs[1].len - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addr & 0x7full) << SW_TWSI_ADDR_SHIFT;

	if (msgs[0].flags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10_IA;
	else
		cmd |= SW_TWSI_OP_7_IA;

	if (msgs[0].len == 2) {
		u64 ext = 0;

		cmd |= SW_TWSI_EIA;
		ext = (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
		cmd |= (u64)msgs[0].buf[1] << SW_TWSI_IA_SHIFT;
		octeon_i2c_writeq_flush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));
	} else {
		cmd |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
	}

	octeon_i2c_hlc_int_clear(i2c);
	octeon_i2c_writeq_flush(cmd, i2c->twsi_base + SW_TWSI(i2c));

	ret = octeon_i2c_hlc_wait(i2c);
	if (ret)
		goto err;

	cmd = __raw_readq(i2c->twsi_base + SW_TWSI(i2c));
	if ((cmd & SW_TWSI_R) == 0)
		return octeon_i2c_check_status(i2c, false);

	for (i = 0, j = msgs[1].len - 1; i  < msgs[1].len && i < 4; i++, j--)
		msgs[1].buf[j] = (cmd >> (8 * i)) & 0xff;

	if (msgs[1].len > 4) {
		cmd = __raw_readq(i2c->twsi_base + SW_TWSI_EXT(i2c));
		for (i = 0; i  < msgs[1].len - 4 && i < 4; i++, j--)
			msgs[1].buf[j] = (cmd >> (8 * i)) & 0xff;
	}

err:
	return ret;
}