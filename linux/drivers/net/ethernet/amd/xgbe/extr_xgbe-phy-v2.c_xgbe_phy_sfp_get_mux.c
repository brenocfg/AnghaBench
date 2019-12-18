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
typedef  int u8 ;
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ sfp_comm; int sfp_mux_channel; int /*<<< orphan*/  sfp_mux_address; } ;
struct xgbe_i2c_op {int len; int* buf; int /*<<< orphan*/  target; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  mux_channel ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_I2C_CMD_WRITE ; 
 scalar_t__ XGBE_SFP_COMM_DIRECT ; 
 int xgbe_phy_i2c_xfer (struct xgbe_prv_data*,struct xgbe_i2c_op*) ; 

__attribute__((used)) static int xgbe_phy_sfp_get_mux(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	struct xgbe_i2c_op i2c_op;
	u8 mux_channel;

	if (phy_data->sfp_comm == XGBE_SFP_COMM_DIRECT)
		return 0;

	/* Select desired mux channel */
	mux_channel = 1 << phy_data->sfp_mux_channel;
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = phy_data->sfp_mux_address;
	i2c_op.len = sizeof(mux_channel);
	i2c_op.buf = &mux_channel;

	return xgbe_phy_i2c_xfer(pdata, &i2c_op);
}