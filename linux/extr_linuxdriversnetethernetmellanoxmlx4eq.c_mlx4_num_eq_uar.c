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
struct TYPE_2__ {int num_comp_vectors; int reserved_eqs; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */

__attribute__((used)) static int mlx4_num_eq_uar(struct mlx4_dev *dev)
{
	/*
	 * Each UAR holds 4 EQ doorbells.  To figure out how many UARs
	 * we need to map, take the difference of highest index and
	 * the lowest index we'll use and add 1.
	 */
	return (dev->caps.num_comp_vectors + 1 + dev->caps.reserved_eqs) / 4 -
		dev->caps.reserved_eqs / 4 + 1;
}