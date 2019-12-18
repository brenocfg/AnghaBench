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
typedef  int u32 ;
struct netlink_ext_ack {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int TCA_CSUM_UPDATE_FLAG_IPV4HDR ; 
 int TCA_CSUM_UPDATE_FLAG_TCP ; 
 int TCA_CSUM_UPDATE_FLAG_UDP ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool csum_offload_supported(struct mlx5e_priv *priv,
				   u32 action,
				   u32 update_flags,
				   struct netlink_ext_ack *extack)
{
	u32 prot_flags = TCA_CSUM_UPDATE_FLAG_IPV4HDR | TCA_CSUM_UPDATE_FLAG_TCP |
			 TCA_CSUM_UPDATE_FLAG_UDP;

	/*  The HW recalcs checksums only if re-writing headers */
	if (!(action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)) {
		NL_SET_ERR_MSG_MOD(extack,
				   "TC csum action is only offloaded with pedit");
		netdev_warn(priv->netdev,
			    "TC csum action is only offloaded with pedit\n");
		return false;
	}

	if (update_flags & ~prot_flags) {
		NL_SET_ERR_MSG_MOD(extack,
				   "can't offload TC csum action for some header/s");
		netdev_warn(priv->netdev,
			    "can't offload TC csum action for some header/s - flags %#x\n",
			    update_flags);
		return false;
	}

	return true;
}