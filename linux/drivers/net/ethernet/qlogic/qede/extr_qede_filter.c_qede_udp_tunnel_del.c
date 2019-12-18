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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tunn_params ;
struct udp_tunnel_info {int type; int /*<<< orphan*/  port; } ;
struct qede_dev {int /*<<< orphan*/  geneve_dst_port; int /*<<< orphan*/  cdev; TYPE_1__* ops; int /*<<< orphan*/  vxlan_dst_port; } ;
struct qed_tunn_params {int update_vxlan_port; int update_geneve_port; int /*<<< orphan*/  geneve_port; int /*<<< orphan*/  vxlan_port; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tunn_config ) (int /*<<< orphan*/ ,struct qed_tunn_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  memset (struct qed_tunn_params*,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_tunn_params*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct qed_tunn_params*) ; 

void qede_udp_tunnel_del(struct net_device *dev,
			 struct udp_tunnel_info *ti)
{
	struct qede_dev *edev = netdev_priv(dev);
	struct qed_tunn_params tunn_params;
	u16 t_port = ntohs(ti->port);

	memset(&tunn_params, 0, sizeof(tunn_params));

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		if (t_port != edev->vxlan_dst_port)
			return;

		tunn_params.update_vxlan_port = 1;
		tunn_params.vxlan_port = 0;

		__qede_lock(edev);
		edev->ops->tunn_config(edev->cdev, &tunn_params);
		__qede_unlock(edev);

		edev->vxlan_dst_port = 0;

		DP_VERBOSE(edev, QED_MSG_DEBUG, "Deleted vxlan port=%d\n",
			   t_port);

		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		if (t_port != edev->geneve_dst_port)
			return;

		tunn_params.update_geneve_port = 1;
		tunn_params.geneve_port = 0;

		__qede_lock(edev);
		edev->ops->tunn_config(edev->cdev, &tunn_params);
		__qede_unlock(edev);

		edev->geneve_dst_port = 0;

		DP_VERBOSE(edev, QED_MSG_DEBUG, "Deleted geneve port=%d\n",
			   t_port);
		break;
	default:
		return;
	}
}