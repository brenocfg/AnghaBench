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
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_TIMING1 ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_bit_change (struct dsi_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_force_tx_stop_mode_io(struct dsi_data *dsi)
{
	u32 r;

	r = dsi_read_reg(dsi, DSI_TIMING1);
	r = FLD_MOD(r, 1, 15, 15);	/* FORCE_TX_STOP_MODE_IO */
	dsi_write_reg(dsi, DSI_TIMING1, r);

	if (!wait_for_bit_change(dsi, DSI_TIMING1, 15, 0)) {
		DSSERR("TX_STOP bit not going down\n");
		return -EIO;
	}

	return 0;
}