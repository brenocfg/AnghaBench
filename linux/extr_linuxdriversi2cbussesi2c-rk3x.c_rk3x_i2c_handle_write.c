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
struct rk3x_i2c {scalar_t__ processed; int /*<<< orphan*/  error; TYPE_1__* msg; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 unsigned int REG_INT_MBTF ; 
 int /*<<< orphan*/  REG_IPD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3x_i2c_clean_ipd (struct rk3x_i2c*) ; 
 int /*<<< orphan*/  rk3x_i2c_fill_transmit_buf (struct rk3x_i2c*) ; 
 int /*<<< orphan*/  rk3x_i2c_stop (struct rk3x_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk3x_i2c_handle_write(struct rk3x_i2c *i2c, unsigned int ipd)
{
	if (!(ipd & REG_INT_MBTF)) {
		rk3x_i2c_stop(i2c, -EIO);
		dev_err(i2c->dev, "unexpected irq in WRITE: 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		return;
	}

	/* ack interrupt */
	i2c_writel(i2c, REG_INT_MBTF, REG_IPD);

	/* are we finished? */
	if (i2c->processed == i2c->msg->len)
		rk3x_i2c_stop(i2c, i2c->error);
	else
		rk3x_i2c_fill_transmit_buf(i2c);
}