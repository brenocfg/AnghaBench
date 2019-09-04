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
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ican3_dev {int num; TYPE_1__* dpm; TYPE_1__* ctrl; int /*<<< orphan*/  irq; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ican3_dev*) ; 
 int /*<<< orphan*/  ican3_shutdown_module (struct ican3_dev*) ; 
 int /*<<< orphan*/  iounmap (TYPE_1__*) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct ican3_dev* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ican3_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct ican3_dev *mod = netdev_priv(ndev);

	/* unregister the netdevice, stop interrupts */
	unregister_netdev(ndev);
	napi_disable(&mod->napi);
	iowrite8(1 << mod->num, &mod->ctrl->int_disable);
	free_irq(mod->irq, mod);

	/* put the module into reset */
	ican3_shutdown_module(mod);

	/* unmap all registers */
	iounmap(mod->ctrl);
	iounmap(mod->dpm);

	free_candev(ndev);

	return 0;
}