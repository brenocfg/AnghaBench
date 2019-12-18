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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct mlx5dr_domain {int dummy; } ;
struct TYPE_2__ {int vlan_hdr; } ;
struct mlx5dr_action {TYPE_1__ push_vlan; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ CVLAN_ETHERTYPE ; 
 int /*<<< orphan*/  DR_ACTION_TYP_PUSH_VLAN ; 
 scalar_t__ SVLAN_ETHERTYPE ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

struct mlx5dr_action *mlx5dr_action_create_push_vlan(struct mlx5dr_domain *dmn,
						     __be32 vlan_hdr)
{
	u32 vlan_hdr_h = ntohl(vlan_hdr);
	u16 ethertype = vlan_hdr_h >> 16;
	struct mlx5dr_action *action;

	if (ethertype != SVLAN_ETHERTYPE && ethertype != CVLAN_ETHERTYPE) {
		mlx5dr_dbg(dmn, "Invalid vlan ethertype\n");
		return NULL;
	}

	action = dr_action_create_generic(DR_ACTION_TYP_PUSH_VLAN);
	if (!action)
		return NULL;

	action->push_vlan.vlan_hdr = vlan_hdr_h;
	return action;
}