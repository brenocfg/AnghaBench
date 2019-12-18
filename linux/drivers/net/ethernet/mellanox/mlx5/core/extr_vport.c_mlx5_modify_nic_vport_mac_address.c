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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  permanent_address; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ field_select ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,void*,int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 int /*<<< orphan*/  nic_vport_context ; 
 int /*<<< orphan*/  other_vport ; 
 int /*<<< orphan*/  permanent_address ; 
 int /*<<< orphan*/  vport_number ; 

int mlx5_modify_nic_vport_mac_address(struct mlx5_core_dev *mdev,
				      u16 vport, u8 *addr)
{
	void *in;
	int inlen = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in);
	int err;
	void *nic_vport_ctx;
	u8 *perm_mac;

	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(modify_nic_vport_context_in, in,
		 field_select.permanent_address, 1);
	MLX5_SET(modify_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(modify_nic_vport_context_in, in, other_vport, 1);

	nic_vport_ctx = MLX5_ADDR_OF(modify_nic_vport_context_in,
				     in, nic_vport_context);
	perm_mac = MLX5_ADDR_OF(nic_vport_context, nic_vport_ctx,
				permanent_address);

	ether_addr_copy(&perm_mac[2], addr);

	err = mlx5_modify_nic_vport_context(mdev, in, inlen);

	kvfree(in);

	return err;
}