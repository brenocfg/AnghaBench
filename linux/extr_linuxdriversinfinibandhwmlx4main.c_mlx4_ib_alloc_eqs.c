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
struct TYPE_4__ {int num_comp_vectors; } ;
struct mlx4_ib_dev {int* eq_table; TYPE_2__ ib_dev; } ;
struct TYPE_3__ {int num_comp_vectors; int num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_assign_eq (struct mlx4_dev*,int,int*) ; 
 int mlx4_get_eqs_per_port (struct mlx4_dev*,int) ; 
 scalar_t__ mlx4_is_eq_shared (struct mlx4_dev*,int) ; 

__attribute__((used)) static void mlx4_ib_alloc_eqs(struct mlx4_dev *dev, struct mlx4_ib_dev *ibdev)
{
	int i, j, eq = 0, total_eqs = 0;

	ibdev->eq_table = kcalloc(dev->caps.num_comp_vectors,
				  sizeof(ibdev->eq_table[0]), GFP_KERNEL);
	if (!ibdev->eq_table)
		return;

	for (i = 1; i <= dev->caps.num_ports; i++) {
		for (j = 0; j < mlx4_get_eqs_per_port(dev, i);
		     j++, total_eqs++) {
			if (i > 1 &&  mlx4_is_eq_shared(dev, total_eqs))
				continue;
			ibdev->eq_table[eq] = total_eqs;
			if (!mlx4_assign_eq(dev, i,
					    &ibdev->eq_table[eq]))
				eq++;
			else
				ibdev->eq_table[eq] = -1;
		}
	}

	for (i = eq; i < dev->caps.num_comp_vectors;
	     ibdev->eq_table[i++] = -1)
		;

	/* Advertise the new number of EQs to clients */
	ibdev->ib_dev.num_comp_vectors = eq;
}