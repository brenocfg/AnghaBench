#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int tdn; } ;
struct TYPE_4__ {int pdn; TYPE_1__ td; } ;
struct mlx5_core_dev {TYPE_2__ mlx5e_res; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tis_in ; 
 int /*<<< orphan*/  ctx ; 
 int mlx5_core_create_tis (struct mlx5_core_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mlx5_lag_is_lacp_owner (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  strict_lag_tx_port_affinity ; 
 int /*<<< orphan*/  tls_en ; 
 int /*<<< orphan*/  transport_domain ; 

int mlx5e_create_tis(struct mlx5_core_dev *mdev, void *in, u32 *tisn)
{
	void *tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

	MLX5_SET(tisc, tisc, transport_domain, mdev->mlx5e_res.td.tdn);

	if (MLX5_GET(tisc, tisc, tls_en))
		MLX5_SET(tisc, tisc, pd, mdev->mlx5e_res.pdn);

	if (mlx5_lag_is_lacp_owner(mdev))
		MLX5_SET(tisc, tisc, strict_lag_tx_port_affinity, 1);

	return mlx5_core_create_tis(mdev, in, MLX5_ST_SZ_BYTES(create_tis_in), tisn);
}