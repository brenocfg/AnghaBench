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
struct mlx4_ib_dev {int dummy; } ;
struct mlx4_eqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BLK_PTR_FROM_EQE (struct mlx4_eqe*) ; 
 int /*<<< orphan*/  GET_MASK_FROM_EQE (struct mlx4_eqe*) ; 
 int /*<<< orphan*/  __propagate_pkey_ev (struct mlx4_ib_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void propagate_pkey_ev(struct mlx4_ib_dev *dev, int port_num,
			      struct mlx4_eqe *eqe)
{
	__propagate_pkey_ev(dev, port_num, GET_BLK_PTR_FROM_EQE(eqe),
			    GET_MASK_FROM_EQE(eqe));
}