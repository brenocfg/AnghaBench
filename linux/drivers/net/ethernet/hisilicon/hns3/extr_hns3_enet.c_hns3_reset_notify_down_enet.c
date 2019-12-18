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
struct net_device {int dummy; } ;
struct hns3_nic_priv {int /*<<< orphan*/  state; } ;
struct hnae3_knic_private_info {struct net_device* netdev; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; int /*<<< orphan*/  pdev; } ;
struct hnae3_ae_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_RESETTING ; 
 int /*<<< orphan*/  hns3_del_all_fd_rules (struct net_device*,int) ; 
 scalar_t__ hns3_dev_ongoing_func_reset (struct hnae3_ae_dev*) ; 
 int hns3_nic_net_stop (struct net_device*) ; 
 int /*<<< orphan*/  hns3_remove_hw_addr (struct net_device*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 struct hnae3_ae_dev* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_reset_notify_down_enet(struct hnae3_handle *handle)
{
	struct hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	struct net_device *ndev = kinfo->netdev;
	struct hns3_nic_priv *priv = netdev_priv(ndev);

	if (test_and_set_bit(HNS3_NIC_STATE_RESETTING, &priv->state))
		return 0;

	/* it is cumbersome for hardware to pick-and-choose entries for deletion
	 * from table space. Hence, for function reset software intervention is
	 * required to delete the entries
	 */
	if (hns3_dev_ongoing_func_reset(ae_dev)) {
		hns3_remove_hw_addr(ndev);
		hns3_del_all_fd_rules(ndev, false);
	}

	if (!netif_running(ndev))
		return 0;

	return hns3_nic_net_stop(ndev);
}