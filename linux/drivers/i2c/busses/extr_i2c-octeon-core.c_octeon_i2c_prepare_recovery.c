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
 int /*<<< orphan*/  SW_TWSI_EOP_TWSI_RST ; 
 int /*<<< orphan*/  TWSI_CTL_ENAB ; 
 struct octeon_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  octeon_i2c_ctl_write (struct octeon_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_i2c_hlc_disable (struct octeon_i2c*) ; 
 int /*<<< orphan*/  octeon_i2c_reg_write (struct octeon_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_i2c_write_int (struct octeon_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void octeon_i2c_prepare_recovery(struct i2c_adapter *adap)
{
	struct octeon_i2c *i2c = i2c_get_adapdata(adap);

	octeon_i2c_hlc_disable(i2c);
	octeon_i2c_reg_write(i2c, SW_TWSI_EOP_TWSI_RST, 0);
	/* wait for software reset to settle */
	udelay(5);

	/*
	 * Bring control register to a good state regardless
	 * of HLC state.
	 */
	octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB);

	octeon_i2c_write_int(i2c, 0);
}