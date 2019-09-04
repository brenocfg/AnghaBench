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
struct mlx5_flow_spec {int* match_value; int* match_criteria; } ;

/* Variables and functions */
 int MLX5_ST_SZ_DW_MATCH_PARAM ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static bool check_valid_spec(const struct mlx5_flow_spec *spec)
{
	int i;

	for (i = 0; i < MLX5_ST_SZ_DW_MATCH_PARAM; i++)
		if (spec->match_value[i] & ~spec->match_criteria[i]) {
			pr_warn("mlx5_core: match_value differs from match_criteria\n");
			return false;
		}

	return true;
}