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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct mlx5dr_domain {int dummy; } ;
struct mlx5dr_action {int dummy; } ;
struct mlx5_fs_vlan {scalar_t__ vid; scalar_t__ prio; scalar_t__ ethtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 struct mlx5dr_action* mlx5dr_action_create_push_vlan (struct mlx5dr_domain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5dr_action *create_action_push_vlan(struct mlx5dr_domain *domain,
						     struct mlx5_fs_vlan *vlan)
{
	u16 n_ethtype = vlan->ethtype;
	u8  prio = vlan->prio;
	u16 vid = vlan->vid;
	u32 vlan_hdr;

	vlan_hdr = (u32)n_ethtype << 16 | (u32)(prio) << 12 |  (u32)vid;
	return mlx5dr_action_create_push_vlan(domain, htonl(vlan_hdr));
}