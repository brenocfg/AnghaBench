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
struct aspeed_i2c_bus {scalar_t__ base; int /*<<< orphan*/  master_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_I2CD_M_STOP_CMD ; 
 scalar_t__ ASPEED_I2C_CMD_REG ; 
 int /*<<< orphan*/  ASPEED_I2C_MASTER_STOP ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void aspeed_i2c_do_stop(struct aspeed_i2c_bus *bus)
{
	bus->master_state = ASPEED_I2C_MASTER_STOP;
	writel(ASPEED_I2CD_M_STOP_CMD, bus->base + ASPEED_I2C_CMD_REG);
}