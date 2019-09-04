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
struct hfi1_vnic_vport_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hfi1_vnic_deinit (struct hfi1_vnic_vport_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct hfi1_vnic_vport_info* opa_vnic_dev_priv (struct net_device*) ; 

__attribute__((used)) static void hfi1_vnic_free_rn(struct net_device *netdev)
{
	struct hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);

	hfi1_vnic_deinit(vinfo);
	mutex_destroy(&vinfo->lock);
	free_netdev(netdev);
}