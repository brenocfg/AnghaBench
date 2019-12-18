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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfp_app {TYPE_1__* pf; } ;
struct net_device {int dummy; } ;
struct ifla_vf_info {int vf; void* linkstate; void* trusted; void* spoofchk; void* qos; void* vlan; int /*<<< orphan*/ * mac; } ;
struct TYPE_2__ {scalar_t__ vfcfg_tbl2; } ;

/* Variables and functions */
 void* FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NFP_NET_VF_CFG_CTRL ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_CTRL_LINK_STATE ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_CTRL_SPOOF ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_CTRL_TRUST ; 
 scalar_t__ NFP_NET_VF_CFG_MAC_LO ; 
 int NFP_NET_VF_CFG_MB_SZ ; 
 int NFP_NET_VF_CFG_SZ ; 
 scalar_t__ NFP_NET_VF_CFG_VLAN ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_VLAN_QOS ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_VLAN_VID ; 
 int /*<<< orphan*/  memset (struct ifla_vf_info*,int /*<<< orphan*/ ,int) ; 
 struct nfp_app* nfp_app_from_netdev (struct net_device*) ; 
 int nfp_net_sriov_check (struct nfp_app*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 

int nfp_app_get_vf_config(struct net_device *netdev, int vf,
			  struct ifla_vf_info *ivi)
{
	struct nfp_app *app = nfp_app_from_netdev(netdev);
	unsigned int vf_offset;
	u16 vlan_tci;
	u32 mac_hi;
	u16 mac_lo;
	u8 flags;
	int err;

	err = nfp_net_sriov_check(app, vf, 0, "");
	if (err)
		return err;

	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;

	mac_hi = readl(app->pf->vfcfg_tbl2 + vf_offset);
	mac_lo = readw(app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_MAC_LO);

	flags = readb(app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_CTRL);
	vlan_tci = readw(app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_VLAN);

	memset(ivi, 0, sizeof(*ivi));
	ivi->vf = vf;

	put_unaligned_be32(mac_hi, &ivi->mac[0]);
	put_unaligned_be16(mac_lo, &ivi->mac[4]);

	ivi->vlan = FIELD_GET(NFP_NET_VF_CFG_VLAN_VID, vlan_tci);
	ivi->qos = FIELD_GET(NFP_NET_VF_CFG_VLAN_QOS, vlan_tci);

	ivi->spoofchk = FIELD_GET(NFP_NET_VF_CFG_CTRL_SPOOF, flags);
	ivi->trusted = FIELD_GET(NFP_NET_VF_CFG_CTRL_TRUST, flags);
	ivi->linkstate = FIELD_GET(NFP_NET_VF_CFG_CTRL_LINK_STATE, flags);

	return 0;
}