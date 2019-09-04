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
typedef  scalar_t__ u32 ;
struct mlx5_wq_qp {int /*<<< orphan*/  sq; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 scalar_t__ mlx5_wq_cyc_get_byte_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 mlx5_wq_qp_get_byte_size(struct mlx5_wq_qp *wq)
{
	return mlx5_wq_cyc_get_byte_size(&wq->rq) +
	       mlx5_wq_cyc_get_byte_size(&wq->sq);
}