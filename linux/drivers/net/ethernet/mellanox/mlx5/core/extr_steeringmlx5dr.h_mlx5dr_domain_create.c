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
struct mlx5dr_domain {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5dr_domain_type { ____Placeholder_mlx5dr_domain_type } mlx5dr_domain_type ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx5dr_domain *
mlx5dr_domain_create(struct mlx5_core_dev *mdev, enum mlx5dr_domain_type type) { return NULL; }