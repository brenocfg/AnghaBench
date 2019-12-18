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
struct nfp_app {TYPE_1__* pf; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpp; scalar_t__ vfcfg_tbl2; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NFP_NET_VF_CFG_MAC_LO ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_MB_CAP_MAC ; 
 int NFP_NET_VF_CFG_MB_SZ ; 
 int /*<<< orphan*/  NFP_NET_VF_CFG_MB_UPD_MAC ; 
 int NFP_NET_VF_CFG_SZ ; 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 struct nfp_app* nfp_app_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  nfp_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int nfp_net_sriov_check (struct nfp_app*,int,int /*<<< orphan*/ ,char*) ; 
 int nfp_net_sriov_update (struct nfp_app*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

int nfp_app_set_vf_mac(struct net_device *netdev, int vf, u8 *mac)
{
	struct nfp_app *app = nfp_app_from_netdev(netdev);
	unsigned int vf_offset;
	int err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_MAC, "mac");
	if (err)
		return err;

	if (is_multicast_ether_addr(mac)) {
		nfp_warn(app->pf->cpp,
			 "invalid Ethernet address %pM for VF id %d\n",
			 mac, vf);
		return -EINVAL;
	}

	/* Write MAC to VF entry in VF config symbol */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	writel(get_unaligned_be32(mac), app->pf->vfcfg_tbl2 + vf_offset);
	writew(get_unaligned_be16(mac + 4),
	       app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_MAC_LO);

	err = nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_MAC, "MAC");
	if (!err)
		nfp_info(app->pf->cpp,
			 "MAC %pM set on VF %d, reload the VF driver to make this change effective.\n",
			 mac, vf);

	return err;
}