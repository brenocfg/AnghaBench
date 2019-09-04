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
struct vnic_dev {struct enic* priv; } ;
struct net_device {int dummy; } ;
struct enic {struct net_device* netdev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct net_device *vnic_get_netdev(struct vnic_dev *vdev)
{
	struct enic *enic = vdev->priv;

	return enic->netdev;
}