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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5dr_ste_htbl {int /*<<< orphan*/  lu_type; } ;
struct mlx5dr_ste {int /*<<< orphan*/ * hw_ste; } ;
struct mlx5dr_htbl_connect_info {scalar_t__ type; int /*<<< orphan*/  miss_icm_addr; int /*<<< orphan*/  hit_next_htbl; } ;
struct mlx5dr_domain_rx_tx {int /*<<< orphan*/  ste_type; } ;

/* Variables and functions */
 scalar_t__ CONNECT_HIT ; 
 int /*<<< orphan*/  dr_ste_always_hit_htbl (struct mlx5dr_ste*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_always_miss_addr (struct mlx5dr_ste*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5dr_ste_set_formatted_ste(u16 gvmi,
				  struct mlx5dr_domain_rx_tx *nic_dmn,
				  struct mlx5dr_ste_htbl *htbl,
				  u8 *formatted_ste,
				  struct mlx5dr_htbl_connect_info *connect_info)
{
	struct mlx5dr_ste ste = {};

	mlx5dr_ste_init(formatted_ste, htbl->lu_type, nic_dmn->ste_type, gvmi);
	ste.hw_ste = formatted_ste;

	if (connect_info->type == CONNECT_HIT)
		dr_ste_always_hit_htbl(&ste, connect_info->hit_next_htbl);
	else
		mlx5dr_ste_always_miss_addr(&ste, connect_info->miss_icm_addr);
}