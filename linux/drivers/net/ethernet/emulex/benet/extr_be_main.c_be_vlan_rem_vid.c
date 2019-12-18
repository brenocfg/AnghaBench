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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct be_adapter {int /*<<< orphan*/  rx_filter_lock; int /*<<< orphan*/  vlans_added; int /*<<< orphan*/  vids; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be_vid_config (struct be_adapter*) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_vlan_rem_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int status = 0;

	mutex_lock(&adapter->rx_filter_lock);

	/* Packets with VID 0 are always received by Lancer by default */
	if (lancer_chip(adapter) && vid == 0)
		goto done;

	if (!test_bit(vid, adapter->vids))
		goto done;

	clear_bit(vid, adapter->vids);
	adapter->vlans_added--;

	status = be_vid_config(adapter);
done:
	mutex_unlock(&adapter->rx_filter_lock);
	return status;
}