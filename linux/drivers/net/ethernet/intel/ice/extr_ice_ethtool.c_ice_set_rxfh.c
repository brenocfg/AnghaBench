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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ice_vsi {int rss_table_size; scalar_t__* rss_lut_user; int /*<<< orphan*/  rss_size; void* rss_hkey_user; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_FLAG_RSS_ENA ; 
 int ICE_VSIQF_HKEY_ARRAY_SIZE ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_fill_rss_lut (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_set_rss (struct ice_vsi*,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__ const*,int) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ice_set_rxfh(struct net_device *netdev, const u32 *indir, const u8 *key,
	     const u8 hfunc)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_pf *pf = vsi->back;
	u8 *seed = NULL;

	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	if (!test_bit(ICE_FLAG_RSS_ENA, pf->flags)) {
		/* RSS not supported return error here */
		netdev_warn(netdev, "RSS is not configured on this VSI!\n");
		return -EIO;
	}

	if (key) {
		if (!vsi->rss_hkey_user) {
			vsi->rss_hkey_user =
				devm_kzalloc(&pf->pdev->dev,
					     ICE_VSIQF_HKEY_ARRAY_SIZE,
					     GFP_KERNEL);
			if (!vsi->rss_hkey_user)
				return -ENOMEM;
		}
		memcpy(vsi->rss_hkey_user, key, ICE_VSIQF_HKEY_ARRAY_SIZE);
		seed = vsi->rss_hkey_user;
	}

	if (!vsi->rss_lut_user) {
		vsi->rss_lut_user = devm_kzalloc(&pf->pdev->dev,
						 vsi->rss_table_size,
						 GFP_KERNEL);
		if (!vsi->rss_lut_user)
			return -ENOMEM;
	}

	/* Each 32 bits pointed by 'indir' is stored with a lut entry */
	if (indir) {
		int i;

		for (i = 0; i < vsi->rss_table_size; i++)
			vsi->rss_lut_user[i] = (u8)(indir[i]);
	} else {
		ice_fill_rss_lut(vsi->rss_lut_user, vsi->rss_table_size,
				 vsi->rss_size);
	}

	if (ice_set_rss(vsi, seed, vsi->rss_lut_user, vsi->rss_table_size))
		return -EIO;

	return 0;
}