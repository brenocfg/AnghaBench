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
struct pca9541 {int select_timeout; int /*<<< orphan*/  arb_timeout; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCA9541_CONTROL ; 
 int PCA9541_CTL_BUSINIT ; 
 int PCA9541_CTL_NTESTON ; 
 int /*<<< orphan*/  PCA9541_ISTAT ; 
 int PCA9541_ISTAT_NMYTEST ; 
 int SELECT_DELAY_LONG ; 
 int SELECT_DELAY_SHORT ; 
 scalar_t__ busoff (int) ; 
 struct i2c_mux_core* i2c_get_clientdata (struct i2c_client*) ; 
 struct pca9541* i2c_mux_priv (struct i2c_mux_core*) ; 
 scalar_t__ mybus (int) ; 
 int* pca9541_control ; 
 int pca9541_reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pca9541_reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_is_before_eq_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca9541_arbitrate(struct i2c_client *client)
{
	struct i2c_mux_core *muxc = i2c_get_clientdata(client);
	struct pca9541 *data = i2c_mux_priv(muxc);
	int reg;

	reg = pca9541_reg_read(client, PCA9541_CONTROL);
	if (reg < 0)
		return reg;

	if (busoff(reg)) {
		int istat;
		/*
		 * Bus is off. Request ownership or turn it on unless
		 * other master requested ownership.
		 */
		istat = pca9541_reg_read(client, PCA9541_ISTAT);
		if (!(istat & PCA9541_ISTAT_NMYTEST)
		    || time_is_before_eq_jiffies(data->arb_timeout)) {
			/*
			 * Other master did not request ownership,
			 * or arbitration timeout expired. Take the bus.
			 */
			pca9541_reg_write(client,
					  PCA9541_CONTROL,
					  pca9541_control[reg & 0x0f]
					  | PCA9541_CTL_NTESTON);
			data->select_timeout = SELECT_DELAY_SHORT;
		} else {
			/*
			 * Other master requested ownership.
			 * Set extra long timeout to give it time to acquire it.
			 */
			data->select_timeout = SELECT_DELAY_LONG * 2;
		}
	} else if (mybus(reg)) {
		/*
		 * Bus is on, and we own it. We are done with acquisition.
		 * Reset NTESTON and BUSINIT, then return success.
		 */
		if (reg & (PCA9541_CTL_NTESTON | PCA9541_CTL_BUSINIT))
			pca9541_reg_write(client,
					  PCA9541_CONTROL,
					  reg & ~(PCA9541_CTL_NTESTON
						  | PCA9541_CTL_BUSINIT));
		return 1;
	} else {
		/*
		 * Other master owns the bus.
		 * If arbitration timeout has expired, force ownership.
		 * Otherwise request it.
		 */
		data->select_timeout = SELECT_DELAY_LONG;
		if (time_is_before_eq_jiffies(data->arb_timeout)) {
			/* Time is up, take the bus and reset it. */
			pca9541_reg_write(client,
					  PCA9541_CONTROL,
					  pca9541_control[reg & 0x0f]
					  | PCA9541_CTL_BUSINIT
					  | PCA9541_CTL_NTESTON);
		} else {
			/* Request bus ownership if needed */
			if (!(reg & PCA9541_CTL_NTESTON))
				pca9541_reg_write(client,
						  PCA9541_CONTROL,
						  reg | PCA9541_CTL_NTESTON);
		}
	}
	return 0;
}