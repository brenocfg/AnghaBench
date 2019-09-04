#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tls_device {int dummy; } ;
struct net_device {int features; } ;
struct chtls_dev {struct net_device** ports; TYPE_1__* lldi; } ;
struct TYPE_2__ {int nports; } ;

/* Variables and functions */
 int NETIF_F_HW_TLS_RECORD ; 
 struct chtls_dev* to_chtls_dev (struct tls_device*) ; 

__attribute__((used)) static int chtls_inline_feature(struct tls_device *dev)
{
	struct net_device *netdev;
	struct chtls_dev *cdev;
	int i;

	cdev = to_chtls_dev(dev);

	for (i = 0; i < cdev->lldi->nports; i++) {
		netdev = cdev->ports[i];
		if (netdev->features & NETIF_F_HW_TLS_RECORD)
			return 1;
	}
	return 0;
}