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
struct dsi_data {int dummy; } ;
typedef  enum dsi_cio_power_state { ____Placeholder_dsi_cio_power_state } dsi_cio_power_state ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_COMPLEXIO_CFG1 ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int ENODEV ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dsi_cio_power(struct dsi_data *dsi, enum dsi_cio_power_state state)
{
	int t = 0;

	/* PWR_CMD */
	REG_FLD_MOD(dsi, DSI_COMPLEXIO_CFG1, state, 28, 27);

	/* PWR_STATUS */
	while (FLD_GET(dsi_read_reg(dsi, DSI_COMPLEXIO_CFG1),
			26, 25) != state) {
		if (++t > 1000) {
			DSSERR("failed to set complexio power state to "
					"%d\n", state);
			return -ENODEV;
		}
		udelay(1);
	}

	return 0;
}