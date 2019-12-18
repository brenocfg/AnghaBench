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
struct mlx5_flow_spec {int dummy; } ;
struct mlx5_flow_act {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ VALID_SPEC_INVALID ; 
 scalar_t__ is_valid_esp_aes_gcm (struct mlx5_core_dev*,struct mlx5_flow_spec const*,struct mlx5_flow_act const*,int) ; 

__attribute__((used)) static bool is_valid_spec(struct mlx5_core_dev *mdev,
			  const struct mlx5_flow_spec *spec,
			  const struct mlx5_flow_act *flow_act,
			  bool egress)
{
	/* We curretly only support ipsec egress flow */
	return is_valid_esp_aes_gcm(mdev, spec, flow_act, egress) != VALID_SPEC_INVALID;
}