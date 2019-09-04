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
struct mlx5_klm {int dummy; } ;
struct mlx5_ib_mr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void mlx5_odp_populate_klm(struct mlx5_klm *pklm, size_t offset,
					 size_t nentries, struct mlx5_ib_mr *mr,
					 int flags) {}