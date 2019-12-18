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
struct mlx5dr_table_rx_tx {int /*<<< orphan*/  s_anchor; int /*<<< orphan*/  default_icm_addr; struct mlx5dr_domain_rx_tx* nic_dmn; } ;
struct mlx5dr_htbl_connect_info {int /*<<< orphan*/  miss_icm_addr; int /*<<< orphan*/  type; } ;
struct mlx5dr_domain_rx_tx {int /*<<< orphan*/  default_icm_addr; } ;
struct mlx5dr_domain {int /*<<< orphan*/  ste_icm_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_MISS ; 
 int /*<<< orphan*/  DR_CHUNK_SIZE_1 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int /*<<< orphan*/  mlx5dr_htbl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_htbl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_htbl_free (int /*<<< orphan*/ ) ; 
 int mlx5dr_ste_htbl_init_and_postsend (struct mlx5dr_domain*,struct mlx5dr_domain_rx_tx*,int /*<<< orphan*/ ,struct mlx5dr_htbl_connect_info*,int) ; 

__attribute__((used)) static int dr_table_init_nic(struct mlx5dr_domain *dmn,
			     struct mlx5dr_table_rx_tx *nic_tbl)
{
	struct mlx5dr_domain_rx_tx *nic_dmn = nic_tbl->nic_dmn;
	struct mlx5dr_htbl_connect_info info;
	int ret;

	nic_tbl->default_icm_addr = nic_dmn->default_icm_addr;

	nic_tbl->s_anchor = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						  DR_CHUNK_SIZE_1,
						  MLX5DR_STE_LU_TYPE_DONT_CARE,
						  0);
	if (!nic_tbl->s_anchor)
		return -ENOMEM;

	info.type = CONNECT_MISS;
	info.miss_icm_addr = nic_dmn->default_icm_addr;
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn,
						nic_tbl->s_anchor,
						&info, true);
	if (ret)
		goto free_s_anchor;

	mlx5dr_htbl_get(nic_tbl->s_anchor);

	return 0;

free_s_anchor:
	mlx5dr_ste_htbl_free(nic_tbl->s_anchor);
	return ret;
}