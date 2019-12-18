#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_eswitch_rep {TYPE_1__* rep_data; } ;
struct TYPE_2__ {struct mlx5_ib_dev* priv; } ;

/* Variables and functions */
 size_t REP_IB ; 

__attribute__((used)) static inline
struct mlx5_ib_dev *mlx5_ib_rep_to_dev(struct mlx5_eswitch_rep *rep)
{
	return rep->rep_data[REP_IB].priv;
}