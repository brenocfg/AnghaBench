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
typedef  int u8 ;
typedef  int u16 ;
struct nfp_app {TYPE_1__* pf; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {scalar_t__ vfcfg_tbl2; int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_MB_CAP_VLAN ; 
 int NFP_NET_VF_CFG_MB_SZ ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_MB_UPD_VLAN ; 
 int NFP_NET_VF_CFG_SZ ; 
 scalar_t__ NFP_NET_VF_CFG_VLAN ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_VLAN_QOS ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_VLAN_VID ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct nfp_app* nfp_app_from_netdev (struct net_device*) ; 
 int nfp_net_sriov_check (struct nfp_app*,int,int /*<<< orphan*/ ,char*) ; 
 int nfp_net_sriov_update (struct nfp_app*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

int nfp_app_set_vf_vlan(struct net_device *netdev, int vf, u16 vlan, u8 qos,
			__be16 vlan_proto)
{
	struct nfp_app *app = nfp_app_from_netdev(netdev);
	unsigned int vf_offset;
	u16 vlan_tci;
	int err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_VLAN, "vlan");
	if (err)
		return err;

	if (vlan_proto != htons(ETH_P_8021Q))
		return -EOPNOTSUPP;

	if (vlan > 4095 || qos > 7) {
		nfp_warn(app->pf->cpp,
			 "invalid vlan id or qos for VF id %d\n", vf);
		return -EINVAL;
	}

	/* Write VLAN tag to VF entry in VF config symbol */
	vlan_tci = FIELD_PREP(NFP_NET_VF_CFG_VLAN_VID, vlan) |
		FIELD_PREP(NFP_NET_VF_CFG_VLAN_QOS, qos);
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	writew(vlan_tci, app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_VLAN);

	return nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_VLAN,
				    "vlan");
}