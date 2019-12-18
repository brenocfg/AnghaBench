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
struct mlx5_ib_qp {int dummy; } ;
struct mlx5_core_rsc_common {int dummy; } ;
struct mlx5_core_qp {int dummy; } ;

/* Variables and functions */
 struct mlx5_ib_qp* to_mibqp (struct mlx5_core_qp*) ; 

__attribute__((used)) static inline struct mlx5_ib_qp *res_to_qp(struct mlx5_core_rsc_common *res)
{
	struct mlx5_core_qp *mqp = (struct mlx5_core_qp *)res;

	return to_mibqp(mqp);
}