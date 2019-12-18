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
struct spider_net_card {int /*<<< orphan*/  tx_timeout_task_counter; int /*<<< orphan*/  waitq; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_CKRCTRL ; 
 int /*<<< orphan*/  SPIDER_NET_CKRCTRL_RUN_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_CKRCTRL_STOP_VALUE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spider_net_undo_pci_setup (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spider_net_remove(struct pci_dev *pdev)
{
	struct net_device *netdev;
	struct spider_net_card *card;

	netdev = pci_get_drvdata(pdev);
	card = netdev_priv(netdev);

	wait_event(card->waitq,
		   atomic_read(&card->tx_timeout_task_counter) == 0);

	unregister_netdev(netdev);

	/* switch off card */
	spider_net_write_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_STOP_VALUE);
	spider_net_write_reg(card, SPIDER_NET_CKRCTRL,
			     SPIDER_NET_CKRCTRL_RUN_VALUE);

	spider_net_undo_pci_setup(card);
	free_netdev(netdev);
}