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
 int hfi1_vnic_up (struct hfi1_vnic_vport_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hfi1_vnic_vport_info* opa_vnic_dev_priv (struct net_device*) ; 

__attribute__((used)) static int hfi1_netdev_open(struct net_device *netdev)
{
	struct hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	int rc;

	mutex_lock(&vinfo->lock);
	rc = hfi1_vnic_up(vinfo);
	mutex_unlock(&vinfo->lock);
	return rc;
}