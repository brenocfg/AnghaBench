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
struct qlcnic_hardware_context {int /*<<< orphan*/  phys_port_id; } ;
struct qlcnic_adapter {int flags; struct qlcnic_hardware_context* ahw; } ;
struct netdev_phys_item_id {int id_len; int /*<<< orphan*/  id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int QLCNIC_HAS_PHYS_PORT_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qlcnic_get_phys_port_id(struct net_device *netdev,
				   struct netdev_phys_item_id *ppid)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	if (!(adapter->flags & QLCNIC_HAS_PHYS_PORT_ID))
		return -EOPNOTSUPP;

	ppid->id_len = sizeof(ahw->phys_port_id);
	memcpy(ppid->id, ahw->phys_port_id, ppid->id_len);

	return 0;
}