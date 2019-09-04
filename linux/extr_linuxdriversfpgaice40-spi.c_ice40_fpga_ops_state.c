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
struct ice40_fpga_priv {int /*<<< orphan*/  cdone; } ;
struct fpga_manager {struct ice40_fpga_priv* priv; } ;
typedef  enum fpga_mgr_states { ____Placeholder_fpga_mgr_states } fpga_mgr_states ;

/* Variables and functions */
 int FPGA_MGR_STATE_OPERATING ; 
 int FPGA_MGR_STATE_UNKNOWN ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fpga_mgr_states ice40_fpga_ops_state(struct fpga_manager *mgr)
{
	struct ice40_fpga_priv *priv = mgr->priv;

	return gpiod_get_value(priv->cdone) ? FPGA_MGR_STATE_OPERATING :
		FPGA_MGR_STATE_UNKNOWN;
}