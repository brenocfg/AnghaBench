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
struct tc_cls_flower_offload {int command; } ;
struct i40e_vsi {int dummy; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 130 
#define  TC_CLSFLOWER_REPLACE 129 
#define  TC_CLSFLOWER_STATS 128 
 int i40e_configure_clsflower (struct i40e_vsi*,struct tc_cls_flower_offload*) ; 
 int i40e_delete_clsflower (struct i40e_vsi*,struct tc_cls_flower_offload*) ; 

__attribute__((used)) static int i40e_setup_tc_cls_flower(struct i40e_netdev_priv *np,
				    struct tc_cls_flower_offload *cls_flower)
{
	struct i40e_vsi *vsi = np->vsi;

	switch (cls_flower->command) {
	case TC_CLSFLOWER_REPLACE:
		return i40e_configure_clsflower(vsi, cls_flower);
	case TC_CLSFLOWER_DESTROY:
		return i40e_delete_clsflower(vsi, cls_flower);
	case TC_CLSFLOWER_STATS:
		return -EOPNOTSUPP;
	default:
		return -EOPNOTSUPP;
	}
}