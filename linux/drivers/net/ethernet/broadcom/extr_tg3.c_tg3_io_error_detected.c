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
struct tg3 {int pcierr_recovery; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  RESET_KIND_SHUTDOWN ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_frozen ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  tg3_full_lock (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_full_unlock (struct tg3*) ; 
 int /*<<< orphan*/  tg3_halt (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_napi_enable (struct tg3*) ; 
 int /*<<< orphan*/  tg3_netif_stop (struct tg3*) ; 
 int /*<<< orphan*/  tg3_phy_stop (struct tg3*) ; 
 int /*<<< orphan*/  tg3_reset_task_cancel (struct tg3*) ; 
 int /*<<< orphan*/  tg3_timer_stop (struct tg3*) ; 

__attribute__((used)) static pci_ers_result_t tg3_io_error_detected(struct pci_dev *pdev,
					      pci_channel_state_t state)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct tg3 *tp = netdev_priv(netdev);
	pci_ers_result_t err = PCI_ERS_RESULT_NEED_RESET;

	netdev_info(netdev, "PCI I/O error detected\n");

	rtnl_lock();

	/* We probably don't have netdev yet */
	if (!netdev || !netif_running(netdev))
		goto done;

	/* We needn't recover from permanent error */
	if (state == pci_channel_io_frozen)
		tp->pcierr_recovery = true;

	tg3_phy_stop(tp);

	tg3_netif_stop(tp);

	tg3_timer_stop(tp);

	/* Want to make sure that the reset task doesn't run */
	tg3_reset_task_cancel(tp);

	netif_device_detach(netdev);

	/* Clean up software state, even if MMIO is blocked */
	tg3_full_lock(tp, 0);
	tg3_halt(tp, RESET_KIND_SHUTDOWN, 0);
	tg3_full_unlock(tp);

done:
	if (state == pci_channel_io_perm_failure) {
		if (netdev) {
			tg3_napi_enable(tp);
			dev_close(netdev);
		}
		err = PCI_ERS_RESULT_DISCONNECT;
	} else {
		pci_disable_device(pdev);
	}

	rtnl_unlock();

	return err;
}