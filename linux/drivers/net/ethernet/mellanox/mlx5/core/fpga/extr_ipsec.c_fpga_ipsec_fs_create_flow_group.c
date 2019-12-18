#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  char u32 ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_root_namespace {struct mlx5_core_dev* dev; } ;
struct mlx5_flow_group {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  outer_esp_spi; } ;
struct TYPE_8__ {TYPE_1__ ft_field_support; } ;
struct TYPE_7__ {int /*<<< orphan*/  misc_parameters; } ;
struct TYPE_6__ {int (* create_flow_group ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*,char*,struct mlx5_flow_group*) ;} ;

/* Variables and functions */
 char* MLX5_ADDR_OF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 char MLX5_GET (int /*<<< orphan*/ ,char*,char) ; 
 char MLX5_MATCH_MISC_PARAMETERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,char*,char,char) ; 
 scalar_t__ MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  egress_to_fs_ft (int) ; 
 TYPE_4__ flow_table_properties_nic_receive ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 TYPE_3__ match_criteria ; 
 int /*<<< orphan*/  memcmp (char*,char*,scalar_t__) ; 
 TYPE_2__* mlx5_fs_cmd_get_default (int /*<<< orphan*/ ) ; 
 char outer_esp_spi ; 

__attribute__((used)) static int fpga_ipsec_fs_create_flow_group(struct mlx5_flow_root_namespace *ns,
					   struct mlx5_flow_table *ft,
					   u32 *in,
					   struct mlx5_flow_group *fg,
					   bool is_egress)
{
	int (*create_flow_group)(struct mlx5_flow_root_namespace *ns,
				 struct mlx5_flow_table *ft, u32 *in,
				 struct mlx5_flow_group *fg) =
		mlx5_fs_cmd_get_default(egress_to_fs_ft(is_egress))->create_flow_group;
	char *misc_params_c = MLX5_ADDR_OF(create_flow_group_in, in,
					   match_criteria.misc_parameters);
	struct mlx5_core_dev *dev = ns->dev;
	u32 saved_outer_esp_spi_mask;
	u8 match_criteria_enable;
	int ret;

	if (MLX5_CAP_FLOWTABLE(dev,
			       flow_table_properties_nic_receive.ft_field_support.outer_esp_spi))
		return create_flow_group(ns, ft, in, fg);

	match_criteria_enable =
		MLX5_GET(create_flow_group_in, in, match_criteria_enable);
	saved_outer_esp_spi_mask =
		MLX5_GET(fte_match_set_misc, misc_params_c, outer_esp_spi);
	if (!match_criteria_enable || !saved_outer_esp_spi_mask)
		return create_flow_group(ns, ft, in, fg);

	MLX5_SET(fte_match_set_misc, misc_params_c, outer_esp_spi, 0);

	if (!(*misc_params_c) &&
	    !memcmp(misc_params_c, misc_params_c + 1, MLX5_ST_SZ_BYTES(fte_match_set_misc) - 1))
		MLX5_SET(create_flow_group_in, in, match_criteria_enable,
			 match_criteria_enable & ~MLX5_MATCH_MISC_PARAMETERS);

	ret = create_flow_group(ns, ft, in, fg);

	MLX5_SET(fte_match_set_misc, misc_params_c, outer_esp_spi, saved_outer_esp_spi_mask);
	MLX5_SET(create_flow_group_in, in, match_criteria_enable, match_criteria_enable);

	return ret;
}