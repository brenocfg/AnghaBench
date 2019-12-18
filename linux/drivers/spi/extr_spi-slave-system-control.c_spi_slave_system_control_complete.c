#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ status; } ;
struct spi_slave_system_control_priv {int /*<<< orphan*/  finished; TYPE_2__* spi; int /*<<< orphan*/  cmd; TYPE_1__ msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CMD_HALT 131 
#define  CMD_POWEROFF 130 
#define  CMD_REBOOT 129 
#define  CMD_SUSPEND 128 
 int /*<<< orphan*/  PM_SUSPEND_MEM ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kernel_halt () ; 
 int /*<<< orphan*/  kernel_power_off () ; 
 int /*<<< orphan*/  kernel_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_suspend (int /*<<< orphan*/ ) ; 
 int spi_slave_system_control_submit (struct spi_slave_system_control_priv*) ; 

__attribute__((used)) static void spi_slave_system_control_complete(void *arg)
{
	struct spi_slave_system_control_priv *priv = arg;
	u16 cmd;
	int ret;

	if (priv->msg.status)
		goto terminate;

	cmd = be16_to_cpu(priv->cmd);
	switch (cmd) {
	case CMD_REBOOT:
		dev_info(&priv->spi->dev, "Rebooting system...\n");
		kernel_restart(NULL);
		break;

	case CMD_POWEROFF:
		dev_info(&priv->spi->dev, "Powering off system...\n");
		kernel_power_off();
		break;

	case CMD_HALT:
		dev_info(&priv->spi->dev, "Halting system...\n");
		kernel_halt();
		break;

	case CMD_SUSPEND:
		dev_info(&priv->spi->dev, "Suspending system...\n");
		pm_suspend(PM_SUSPEND_MEM);
		break;

	default:
		dev_warn(&priv->spi->dev, "Unknown command 0x%x\n", cmd);
		break;
	}

	ret = spi_slave_system_control_submit(priv);
	if (ret)
		goto terminate;

	return;

terminate:
	dev_info(&priv->spi->dev, "Terminating\n");
	complete(&priv->finished);
}