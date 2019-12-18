#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sunqe {struct platform_device* op; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct linux_prom_registers {int which_io; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct sunqe* netdev_priv (struct net_device*) ; 
 struct linux_prom_registers* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void qe_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	const struct linux_prom_registers *regs;
	struct sunqe *qep = netdev_priv(dev);
	struct platform_device *op;

	strlcpy(info->driver, "sunqe", sizeof(info->driver));
	strlcpy(info->version, "3.0", sizeof(info->version));

	op = qep->op;
	regs = of_get_property(op->dev.of_node, "reg", NULL);
	if (regs)
		snprintf(info->bus_info, sizeof(info->bus_info), "SBUS:%d",
			 regs->which_io);

}