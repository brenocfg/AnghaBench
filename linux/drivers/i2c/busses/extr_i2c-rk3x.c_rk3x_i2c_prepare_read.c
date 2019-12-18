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
typedef  unsigned int u32 ;
struct rk3x_i2c {unsigned int processed; TYPE_1__* msg; } ;
struct TYPE_2__ {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CON ; 
 unsigned int REG_CON_LASTACK ; 
 unsigned int REG_CON_MOD (int /*<<< orphan*/ ) ; 
 unsigned int REG_CON_MOD_MASK ; 
 int /*<<< orphan*/  REG_CON_MOD_RX ; 
 int /*<<< orphan*/  REG_MRXCNT ; 
 unsigned int i2c_readl (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk3x_i2c_prepare_read(struct rk3x_i2c *i2c)
{
	unsigned int len = i2c->msg->len - i2c->processed;
	u32 con;

	con = i2c_readl(i2c, REG_CON);

	/*
	 * The hw can read up to 32 bytes at a time. If we need more than one
	 * chunk, send an ACK after the last byte of the current chunk.
	 */
	if (len > 32) {
		len = 32;
		con &= ~REG_CON_LASTACK;
	} else {
		con |= REG_CON_LASTACK;
	}

	/* make sure we are in plain RX mode if we read a second chunk */
	if (i2c->processed != 0) {
		con &= ~REG_CON_MOD_MASK;
		con |= REG_CON_MOD(REG_CON_MOD_RX);
	}

	i2c_writel(i2c, con, REG_CON);
	i2c_writel(i2c, len, REG_MRXCNT);
}