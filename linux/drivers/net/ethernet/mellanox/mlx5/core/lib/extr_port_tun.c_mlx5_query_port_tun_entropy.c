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
struct mlx5_port_tun_entropy_flags {int force_supported; int calc_supported; int gre_calc_supported; int force_enabled; int calc_enabled; int gre_calc_enabled; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entropy_calc ; 
 int /*<<< orphan*/  entropy_calc_cap ; 
 int /*<<< orphan*/  entropy_force ; 
 int /*<<< orphan*/  entropy_force_cap ; 
 int /*<<< orphan*/  entropy_gre_calc ; 
 int /*<<< orphan*/  entropy_gre_calc_cap ; 
 scalar_t__ mlx5_query_ports_check (struct mlx5_core_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcmr_reg ; 
 int /*<<< orphan*/  ports_check ; 

__attribute__((used)) static void mlx5_query_port_tun_entropy(struct mlx5_core_dev *mdev,
					struct mlx5_port_tun_entropy_flags *entropy_flags)
{
	u32 out[MLX5_ST_SZ_DW(pcmr_reg)];
	/* Default values for FW which do not support MLX5_REG_PCMR */
	entropy_flags->force_supported = false;
	entropy_flags->calc_supported = false;
	entropy_flags->gre_calc_supported = false;
	entropy_flags->force_enabled = false;
	entropy_flags->calc_enabled = true;
	entropy_flags->gre_calc_enabled = true;

	if (!MLX5_CAP_GEN(mdev, ports_check))
		return;

	if (mlx5_query_ports_check(mdev, out, sizeof(out)))
		return;

	entropy_flags->force_supported = !!(MLX5_GET(pcmr_reg, out, entropy_force_cap));
	entropy_flags->calc_supported = !!(MLX5_GET(pcmr_reg, out, entropy_calc_cap));
	entropy_flags->gre_calc_supported = !!(MLX5_GET(pcmr_reg, out, entropy_gre_calc_cap));
	entropy_flags->force_enabled = !!(MLX5_GET(pcmr_reg, out, entropy_force));
	entropy_flags->calc_enabled = !!(MLX5_GET(pcmr_reg, out, entropy_calc));
	entropy_flags->gre_calc_enabled = !!(MLX5_GET(pcmr_reg, out, entropy_gre_calc));
}