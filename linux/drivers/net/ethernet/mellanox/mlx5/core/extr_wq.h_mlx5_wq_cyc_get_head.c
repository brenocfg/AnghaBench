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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_wq_cyc {int /*<<< orphan*/  wqe_ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 mlx5_wq_cyc_get_head(struct mlx5_wq_cyc *wq)
{
	return mlx5_wq_cyc_ctr2ix(wq, wq->wqe_ctr);
}