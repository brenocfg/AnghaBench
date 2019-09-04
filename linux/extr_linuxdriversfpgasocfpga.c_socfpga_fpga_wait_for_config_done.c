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
struct socfpga_fpga_priv {int /*<<< orphan*/  status_complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_MON_CONF_DONE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  socfpga_fpga_disable_irqs (struct socfpga_fpga_priv*) ; 
 int /*<<< orphan*/  socfpga_fpga_enable_irqs (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socfpga_fpga_wait_for_config_done(struct socfpga_fpga_priv *priv)
{
	int timeout, ret = 0;

	socfpga_fpga_disable_irqs(priv);
	init_completion(&priv->status_complete);
	socfpga_fpga_enable_irqs(priv, SOCFPGA_FPGMGR_MON_CONF_DONE);

	timeout = wait_for_completion_interruptible_timeout(
						&priv->status_complete,
						msecs_to_jiffies(10));
	if (timeout == 0)
		ret = -ETIMEDOUT;

	socfpga_fpga_disable_irqs(priv);
	return ret;
}