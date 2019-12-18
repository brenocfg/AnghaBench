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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct iavf_mac_filter {int remove; } ;
struct iavf_adapter {int /*<<< orphan*/  aq_required; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_FLAG_AQ_DEL_MAC_FILTER ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct iavf_mac_filter* iavf_find_filter (struct iavf_adapter*,int /*<<< orphan*/  const*) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int iavf_addr_unsync(struct net_device *netdev, const u8 *addr)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);
	struct iavf_mac_filter *f;

	/* Under some circumstances, we might receive a request to delete
	 * our own device address from our uc list. Because we store the
	 * device address in the VSI's MAC/VLAN filter list, we need to ignore
	 * such requests and not delete our device address from this list.
	 */
	if (ether_addr_equal(addr, netdev->dev_addr))
		return 0;

	f = iavf_find_filter(adapter, addr);
	if (f) {
		f->remove = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_MAC_FILTER;
	}
	return 0;
}