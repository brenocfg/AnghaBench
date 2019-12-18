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
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_priv_flags {int flag; } ;
struct TYPE_2__ {scalar_t__ pf_id; } ;
struct i40e_pf {int flags; TYPE_1__ hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 size_t I40E_GL_PRIV_FLAGS_STR_LEN ; 
 size_t I40E_PRIV_FLAGS_STR_LEN ; 
 struct i40e_priv_flags* i40e_gl_gstrings_priv_flags ; 
 struct i40e_priv_flags* i40e_gstrings_priv_flags ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 i40e_get_priv_flags(struct net_device *dev)
{
	struct i40e_netdev_priv *np = netdev_priv(dev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	u32 i, j, ret_flags = 0;

	for (i = 0; i < I40E_PRIV_FLAGS_STR_LEN; i++) {
		const struct i40e_priv_flags *priv_flags;

		priv_flags = &i40e_gstrings_priv_flags[i];

		if (priv_flags->flag & pf->flags)
			ret_flags |= BIT(i);
	}

	if (pf->hw.pf_id != 0)
		return ret_flags;

	for (j = 0; j < I40E_GL_PRIV_FLAGS_STR_LEN; j++) {
		const struct i40e_priv_flags *priv_flags;

		priv_flags = &i40e_gl_gstrings_priv_flags[j];

		if (priv_flags->flag & pf->flags)
			ret_flags |= BIT(i + j);
	}

	return ret_flags;
}