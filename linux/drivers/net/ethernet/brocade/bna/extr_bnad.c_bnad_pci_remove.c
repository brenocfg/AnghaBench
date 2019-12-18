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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hb_timer; int /*<<< orphan*/  sem_timer; int /*<<< orphan*/  ioc_timer; } ;
struct TYPE_4__ {TYPE_1__ ioc; } ;
struct bna {TYPE_2__ ioceth; } ;
struct bnad {int /*<<< orphan*/  regdata; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/ * res_info; int /*<<< orphan*/ * mod_res_info; int /*<<< orphan*/  bna_lock; struct bna bna; int /*<<< orphan*/  run_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_NETDEV_REGISTERED ; 
 int /*<<< orphan*/  BNA_MOD_RES_T_MAX ; 
 int /*<<< orphan*/  BNA_RES_T_MAX ; 
 int /*<<< orphan*/  bna_uninit (struct bna*) ; 
 int /*<<< orphan*/  bnad_debugfs_uninit (struct bnad*) ; 
 int /*<<< orphan*/  bnad_disable_msix (struct bnad*) ; 
 int /*<<< orphan*/  bnad_ioceth_disable (struct bnad*) ; 
 int /*<<< orphan*/  bnad_lock_uninit (struct bnad*) ; 
 int /*<<< orphan*/  bnad_mbox_irq_free (struct bnad*) ; 
 int /*<<< orphan*/  bnad_pci_uninit (struct pci_dev*) ; 
 int /*<<< orphan*/  bnad_res_free (struct bnad*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_uninit (struct bnad*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
bnad_pci_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct bnad *bnad;
	struct bna *bna;
	unsigned long flags;

	if (!netdev)
		return;

	bnad = netdev_priv(netdev);
	bna = &bnad->bna;

	if (test_and_clear_bit(BNAD_RF_NETDEV_REGISTERED, &bnad->run_flags))
		unregister_netdev(netdev);

	mutex_lock(&bnad->conf_mutex);
	bnad_ioceth_disable(bnad);
	del_timer_sync(&bnad->bna.ioceth.ioc.ioc_timer);
	del_timer_sync(&bnad->bna.ioceth.ioc.sem_timer);
	del_timer_sync(&bnad->bna.ioceth.ioc.hb_timer);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_uninit(bna);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad_res_free(bnad, &bnad->mod_res_info[0], BNA_MOD_RES_T_MAX);
	bnad_res_free(bnad, &bnad->res_info[0], BNA_RES_T_MAX);
	bnad_mbox_irq_free(bnad);
	bnad_disable_msix(bnad);
	bnad_pci_uninit(pdev);
	mutex_unlock(&bnad->conf_mutex);
	bnad_lock_uninit(bnad);
	/* Remove the debugfs node for this bnad */
	kfree(bnad->regdata);
	bnad_debugfs_uninit(bnad);
	bnad_uninit(bnad);
	free_netdev(netdev);
}