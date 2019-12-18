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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct img_i2c {int /*<<< orphan*/  int_enable; TYPE_1__ msg; } ;

/* Variables and functions */
 int FIFO_WRITE_FULL ; 
 int /*<<< orphan*/  INT_FIFO_EMPTYING ; 
 int /*<<< orphan*/  SCB_FIFO_STATUS_REG ; 
 int /*<<< orphan*/  SCB_WRITE_DATA_REG ; 
 int img_i2c_readl (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_wr_rd_fence (struct img_i2c*) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_i2c_write_fifo(struct img_i2c *i2c)
{
	while (i2c->msg.len) {
		u32 fifo_status;

		img_i2c_wr_rd_fence(i2c);
		fifo_status = img_i2c_readl(i2c, SCB_FIFO_STATUS_REG);
		if (fifo_status & FIFO_WRITE_FULL)
			break;

		img_i2c_writel(i2c, SCB_WRITE_DATA_REG, *i2c->msg.buf);
		i2c->msg.len--;
		i2c->msg.buf++;
	}

	/* Disable fifo emptying interrupt if nothing more to write */
	if (!i2c->msg.len)
		i2c->int_enable &= ~INT_FIFO_EMPTYING;
}