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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct i40e_vsi {scalar_t__* rss_lut_user; int /*<<< orphan*/  rss_size; void* rss_hkey_user; struct i40e_pf* back; } ;
struct i40e_pf {int dummy; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t I40E_HKEY_ARRAY_SIZE ; 
 size_t I40E_HLUT_ARRAY_SIZE ; 
 int i40e_config_rss (struct i40e_vsi*,scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  i40e_fill_rss_lut (struct i40e_pf*,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__ const*,size_t) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_set_rxfh(struct net_device *netdev, const u32 *indir,
			 const u8 *key, const u8 hfunc)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	u8 *seed = NULL;
	u16 i;

	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	if (key) {
		if (!vsi->rss_hkey_user) {
			vsi->rss_hkey_user = kzalloc(I40E_HKEY_ARRAY_SIZE,
						     GFP_KERNEL);
			if (!vsi->rss_hkey_user)
				return -ENOMEM;
		}
		memcpy(vsi->rss_hkey_user, key, I40E_HKEY_ARRAY_SIZE);
		seed = vsi->rss_hkey_user;
	}
	if (!vsi->rss_lut_user) {
		vsi->rss_lut_user = kzalloc(I40E_HLUT_ARRAY_SIZE, GFP_KERNEL);
		if (!vsi->rss_lut_user)
			return -ENOMEM;
	}

	/* Each 32 bits pointed by 'indir' is stored with a lut entry */
	if (indir)
		for (i = 0; i < I40E_HLUT_ARRAY_SIZE; i++)
			vsi->rss_lut_user[i] = (u8)(indir[i]);
	else
		i40e_fill_rss_lut(pf, vsi->rss_lut_user, I40E_HLUT_ARRAY_SIZE,
				  vsi->rss_size);

	return i40e_config_rss(vsi, seed, vsi->rss_lut_user,
			       I40E_HLUT_ARRAY_SIZE);
}