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
typedef  int /*<<< orphan*/  u32 ;
struct zx2967_i2c {scalar_t__ msg_rd; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_RFIFO_RESET ; 
 int /*<<< orphan*/  I2C_WFIFO_RESET ; 
 int /*<<< orphan*/  REG_RDCONF ; 
 int /*<<< orphan*/  REG_WRCONF ; 
 int /*<<< orphan*/  zx2967_i2c_readl (struct zx2967_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_i2c_writel (struct zx2967_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx2967_i2c_flush_fifos(struct zx2967_i2c *i2c)
{
	u32 offset;
	u32 val;

	if (i2c->msg_rd) {
		offset = REG_RDCONF;
		val = I2C_RFIFO_RESET;
	} else {
		offset = REG_WRCONF;
		val = I2C_WFIFO_RESET;
	}

	val |= zx2967_i2c_readl(i2c, offset);
	zx2967_i2c_writel(i2c, val, offset);
}