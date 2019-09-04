#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_4__ {scalar_t__ pf_id; } ;
struct i40e_pf {TYPE_1__ hw; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
struct TYPE_6__ {char* flag_string; } ;
struct TYPE_5__ {char* flag_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 unsigned int I40E_GL_PRIV_FLAGS_STR_LEN ; 
 unsigned int I40E_PRIV_FLAGS_STR_LEN ; 
 TYPE_3__* i40e_gl_gstrings_priv_flags ; 
 TYPE_2__* i40e_gstrings_priv_flags ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void i40e_get_priv_flag_strings(struct net_device *netdev, u8 *data)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	char *p = (char *)data;
	unsigned int i;

	for (i = 0; i < I40E_PRIV_FLAGS_STR_LEN; i++) {
		snprintf(p, ETH_GSTRING_LEN, "%s",
			 i40e_gstrings_priv_flags[i].flag_string);
		p += ETH_GSTRING_LEN;
	}
	if (pf->hw.pf_id != 0)
		return;
	for (i = 0; i < I40E_GL_PRIV_FLAGS_STR_LEN; i++) {
		snprintf(p, ETH_GSTRING_LEN, "%s",
			 i40e_gl_gstrings_priv_flags[i].flag_string);
		p += ETH_GSTRING_LEN;
	}
}