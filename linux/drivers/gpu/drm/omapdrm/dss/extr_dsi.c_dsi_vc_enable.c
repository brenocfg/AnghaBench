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

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int) ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int EIO ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_bit_change (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dsi_vc_enable(struct dsi_data *dsi, int channel, bool enable)
{
	DSSDBG("dsi_vc_enable channel %d, enable %d\n",
			channel, enable);

	enable = enable ? 1 : 0;

	REG_FLD_MOD(dsi, DSI_VC_CTRL(channel), enable, 0, 0);

	if (!wait_for_bit_change(dsi, DSI_VC_CTRL(channel), 0, enable)) {
		DSSERR("Failed to set dsi_vc_enable to %d\n", enable);
		return -EIO;
	}

	return 0;
}