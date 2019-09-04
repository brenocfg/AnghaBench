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
typedef  int u32 ;
struct cdns_i2c {int dummy; } ;

/* Variables and functions */
 int CDNS_I2C_CR_HOLD ; 
 int /*<<< orphan*/  CDNS_I2C_CR_OFFSET ; 
 int cdns_i2c_readreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_i2c_writereg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns_i2c_clear_bus_hold(struct cdns_i2c *id)
{
	u32 reg = cdns_i2c_readreg(CDNS_I2C_CR_OFFSET);
	if (reg & CDNS_I2C_CR_HOLD)
		cdns_i2c_writereg(reg & ~CDNS_I2C_CR_HOLD, CDNS_I2C_CR_OFFSET);
}