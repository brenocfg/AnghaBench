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
struct mlx5dr_table {int dummy; } ;
struct mlx5dr_matcher {int dummy; } ;
struct mlx5dr_match_parameters {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx5dr_matcher *
mlx5dr_matcher_create(struct mlx5dr_table *table,
		      u16 priority,
		      u8 match_criteria_enable,
		      struct mlx5dr_match_parameters *mask) { return NULL; }