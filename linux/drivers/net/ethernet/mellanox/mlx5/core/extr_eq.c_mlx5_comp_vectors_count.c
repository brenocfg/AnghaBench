#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* eq_table; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_3__ {unsigned int num_comp_eqs; } ;

/* Variables and functions */

unsigned int mlx5_comp_vectors_count(struct mlx5_core_dev *dev)
{
	return dev->priv.eq_table->num_comp_eqs;
}