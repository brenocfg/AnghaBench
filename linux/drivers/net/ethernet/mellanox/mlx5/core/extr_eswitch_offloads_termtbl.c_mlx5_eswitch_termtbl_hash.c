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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vhca_id; int /*<<< orphan*/  num; } ;
struct mlx5_flow_destination {TYPE_1__ vport; } ;
struct mlx5_flow_act {int /*<<< orphan*/  vlan; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
mlx5_eswitch_termtbl_hash(struct mlx5_flow_act *flow_act,
			  struct mlx5_flow_destination *dest)
{
	u32 hash;

	hash = jhash_1word(flow_act->action, 0);
	hash = jhash((const void *)&flow_act->vlan,
		     sizeof(flow_act->vlan), hash);
	hash = jhash((const void *)&dest->vport.num,
		     sizeof(dest->vport.num), hash);
	hash = jhash((const void *)&dest->vport.vhca_id,
		     sizeof(dest->vport.num), hash);
	return hash;
}