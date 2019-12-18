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
struct nfp_fl_lag {int dummy; } ;
struct nfp_flower_priv {struct nfp_fl_lag nfp_lag; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGELOWERSTATE 130 
#define  NETDEV_CHANGEUPPER 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  nfp_fl_lag_changels_event (struct nfp_fl_lag*,struct net_device*,void*) ; 
 int nfp_fl_lag_changeupper_event (struct nfp_fl_lag*,void*) ; 
 int /*<<< orphan*/  nfp_fl_lag_schedule_group_delete (struct nfp_fl_lag*,struct net_device*) ; 

int nfp_flower_lag_netdev_event(struct nfp_flower_priv *priv,
				struct net_device *netdev,
				unsigned long event, void *ptr)
{
	struct nfp_fl_lag *lag = &priv->nfp_lag;
	int err;

	switch (event) {
	case NETDEV_CHANGEUPPER:
		err = nfp_fl_lag_changeupper_event(lag, ptr);
		if (err)
			return NOTIFY_BAD;
		return NOTIFY_OK;
	case NETDEV_CHANGELOWERSTATE:
		nfp_fl_lag_changels_event(lag, netdev, ptr);
		return NOTIFY_OK;
	case NETDEV_UNREGISTER:
		nfp_fl_lag_schedule_group_delete(lag, netdev);
		return NOTIFY_OK;
	}

	return NOTIFY_DONE;
}