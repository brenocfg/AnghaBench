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
struct mlx5_ib_dev {int dummy; } ;
struct ib_umem {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 void __mlx5_ib_populate_pas (struct mlx5_ib_dev*,struct ib_umem*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ib_umem_num_pages (struct ib_umem*) ; 

void mlx5_ib_populate_pas(struct mlx5_ib_dev *dev, struct ib_umem *umem,
			  int page_shift, __be64 *pas, int access_flags)
{
	return __mlx5_ib_populate_pas(dev, umem, page_shift, 0,
				      ib_umem_num_pages(umem), pas,
				      access_flags);
}