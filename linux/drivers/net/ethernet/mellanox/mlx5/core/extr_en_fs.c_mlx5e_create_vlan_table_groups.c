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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_flow_table {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int __mlx5e_create_vlan_table_groups (struct mlx5e_flow_table*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_create_vlan_table_groups(struct mlx5e_flow_table *ft)
{
	u32 *in;
	int inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	int err;

	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	err = __mlx5e_create_vlan_table_groups(ft, in, inlen);

	kvfree(in);
	return err;
}