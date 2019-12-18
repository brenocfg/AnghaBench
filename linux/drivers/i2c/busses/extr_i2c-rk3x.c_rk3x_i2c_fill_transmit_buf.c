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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct rk3x_i2c {scalar_t__ processed; int addr; TYPE_1__* msg; } ;
struct TYPE_2__ {scalar_t__ len; unsigned int* buf; } ;

/* Variables and functions */
 scalar_t__ REG_MTXCNT ; 
 scalar_t__ TXBUFFER_BASE ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,unsigned int,scalar_t__) ; 

__attribute__((used)) static void rk3x_i2c_fill_transmit_buf(struct rk3x_i2c *i2c)
{
	unsigned int i, j;
	u32 cnt = 0;
	u32 val;
	u8 byte;

	for (i = 0; i < 8; ++i) {
		val = 0;
		for (j = 0; j < 4; ++j) {
			if ((i2c->processed == i2c->msg->len) && (cnt != 0))
				break;

			if (i2c->processed == 0 && cnt == 0)
				byte = (i2c->addr & 0x7f) << 1;
			else
				byte = i2c->msg->buf[i2c->processed++];

			val |= byte << (j * 8);
			cnt++;
		}

		i2c_writel(i2c, val, TXBUFFER_BASE + 4 * i);

		if (i2c->processed == i2c->msg->len)
			break;
	}

	i2c_writel(i2c, cnt, REG_MTXCNT);
}