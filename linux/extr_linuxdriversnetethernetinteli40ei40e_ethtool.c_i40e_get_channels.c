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
struct net_device {int dummy; } ;
struct i40e_vsi {int /*<<< orphan*/  num_queue_pairs; struct i40e_pf* back; } ;
struct i40e_pf {int flags; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct ethtool_channels {int other_count; int max_other; int /*<<< orphan*/  combined_count; int /*<<< orphan*/  max_combined; } ;

/* Variables and functions */
 int I40E_FLAG_FD_SB_ENABLED ; 
 int /*<<< orphan*/  i40e_max_channels (struct i40e_vsi*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40e_get_channels(struct net_device *dev,
			      struct ethtool_channels *ch)
{
	struct i40e_netdev_priv *np = netdev_priv(dev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;

	/* report maximum channels */
	ch->max_combined = i40e_max_channels(vsi);

	/* report info for other vector */
	ch->other_count = (pf->flags & I40E_FLAG_FD_SB_ENABLED) ? 1 : 0;
	ch->max_other = ch->other_count;

	/* Note: This code assumes DCB is disabled for now. */
	ch->combined_count = vsi->num_queue_pairs;
}