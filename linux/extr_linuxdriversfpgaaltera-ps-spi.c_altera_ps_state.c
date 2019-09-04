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
struct fpga_manager {struct altera_ps_conf* priv; } ;
struct altera_ps_conf {int /*<<< orphan*/  status; } ;
typedef  enum fpga_mgr_states { ____Placeholder_fpga_mgr_states } fpga_mgr_states ;

/* Variables and functions */
 int FPGA_MGR_STATE_RESET ; 
 int FPGA_MGR_STATE_UNKNOWN ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum fpga_mgr_states altera_ps_state(struct fpga_manager *mgr)
{
	struct altera_ps_conf *conf = mgr->priv;

	if (gpiod_get_value_cansleep(conf->status))
		return FPGA_MGR_STATE_RESET;

	return FPGA_MGR_STATE_UNKNOWN;
}