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
struct xlnx_pr_decoupler_data {int /*<<< orphan*/  clk; } ;
struct fpga_bridge {struct xlnx_pr_decoupler_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_CMD_COUPLE ; 
 int /*<<< orphan*/  CTRL_CMD_DECOUPLE ; 
 int /*<<< orphan*/  CTRL_OFFSET ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlnx_pr_decoupler_write (struct xlnx_pr_decoupler_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlnx_pr_decoupler_enable_set(struct fpga_bridge *bridge, bool enable)
{
	int err;
	struct xlnx_pr_decoupler_data *priv = bridge->priv;

	err = clk_enable(priv->clk);
	if (err)
		return err;

	if (enable)
		xlnx_pr_decoupler_write(priv, CTRL_OFFSET, CTRL_CMD_COUPLE);
	else
		xlnx_pr_decoupler_write(priv, CTRL_OFFSET, CTRL_CMD_DECOUPLE);

	clk_disable(priv->clk);

	return 0;
}