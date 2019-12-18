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
struct mlx5dr_rule {int dummy; } ;
struct mlx5dr_matcher {int dummy; } ;
struct mlx5dr_match_parameters {int dummy; } ;
struct mlx5dr_action {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx5dr_rule *
mlx5dr_rule_create(struct mlx5dr_matcher *matcher,
		   struct mlx5dr_match_parameters *value,
		   size_t num_actions,
		   struct mlx5dr_action *actions[]) { return NULL; }