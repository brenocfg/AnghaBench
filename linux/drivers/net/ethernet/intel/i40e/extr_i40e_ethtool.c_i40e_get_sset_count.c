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
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_2__ {int /*<<< orphan*/  pf_id; } ;
struct i40e_pf {TYPE_1__ hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int /*<<< orphan*/  I40E_GL_PRIV_FLAGS_STR_LEN ; 
 int /*<<< orphan*/  I40E_PRIV_FLAGS_STR_LEN ; 
 int I40E_TEST_LEN ; 
 int i40e_get_stats_count (struct net_device*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_get_sset_count(struct net_device *netdev, int sset)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;

	switch (sset) {
	case ETH_SS_TEST:
		return I40E_TEST_LEN;
	case ETH_SS_STATS:
		return i40e_get_stats_count(netdev);
	case ETH_SS_PRIV_FLAGS:
		return I40E_PRIV_FLAGS_STR_LEN +
			(pf->hw.pf_id == 0 ? I40E_GL_PRIV_FLAGS_STR_LEN : 0);
	default:
		return -EOPNOTSUPP;
	}
}