#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wpa; } ;
typedef  TYPE_1__ islpci_private ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_get_wpa(struct net_device *ndev, struct iw_request_info *info,
		__u32 * uwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	*uwrq = priv->wpa;
	return 0;
}