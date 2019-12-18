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
struct net_device {int dummy; } ;
struct TYPE_2__ {int* buff; int qtail; } ;
struct ks_wlan_private {TYPE_1__ hostt; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int SME_EVENT_BUFF_SIZE ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  print_hif_event (struct net_device*,int) ; 

__attribute__((used)) static int ks_wlan_hostt(struct net_device *dev, struct iw_request_info *info,
			 __u32 *uwrq, char *extra)
{
	int i, event;
	struct ks_wlan_private *priv = netdev_priv(dev);

	for (i = 63; i >= 0; i--) {
		event =
		    priv->hostt.buff[(priv->hostt.qtail - 1 - i) %
				     SME_EVENT_BUFF_SIZE];
		print_hif_event(dev, event);
	}
	return 0;
}