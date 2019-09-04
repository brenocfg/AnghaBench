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
struct octeon_i2c {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int TWSI_INT_SCL_OVR ; 
 int TWSI_INT_SDA_OVR ; 
 struct octeon_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  octeon_i2c_write_int (struct octeon_i2c*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void octeon_i2c_unprepare_recovery(struct i2c_adapter *adap)
{
	struct octeon_i2c *i2c = i2c_get_adapdata(adap);

	/*
	 * Generate STOP to finish the unfinished transaction.
	 * Can't generate STOP via the TWSI CTL register
	 * since it could bring the TWSI controller into an inoperable state.
	 */
	octeon_i2c_write_int(i2c, TWSI_INT_SDA_OVR | TWSI_INT_SCL_OVR);
	udelay(5);
	octeon_i2c_write_int(i2c, TWSI_INT_SDA_OVR);
	udelay(5);
	octeon_i2c_write_int(i2c, 0);
}