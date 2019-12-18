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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;
struct TYPE_2__ {int /*<<< orphan*/  bth_dst_qp; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE_NIC_RX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bth_dst_qp ; 
 TYPE_1__ ft_field_support ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  misc_parameters ; 

__attribute__((used)) static void set_underlay_qp(struct mlx5_ib_dev *dev,
			    struct mlx5_flow_spec *spec,
			    u32 underlay_qpn)
{
	void *misc_params_c = MLX5_ADDR_OF(fte_match_param,
					   spec->match_criteria,
					   misc_parameters);
	void *misc_params_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
					   misc_parameters);

	if (underlay_qpn &&
	    MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
				      ft_field_support.bth_dst_qp)) {
		MLX5_SET(fte_match_set_misc,
			 misc_params_v, bth_dst_qp, underlay_qpn);
		MLX5_SET(fte_match_set_misc,
			 misc_params_c, bth_dst_qp, 0xffffff);
	}
}