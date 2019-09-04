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
struct mlx5e_hairpin {int /*<<< orphan*/  tdn; int /*<<< orphan*/  func_mdev; int /*<<< orphan*/  tirn; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dealloc_transport_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_tir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_hairpin_destroy_transport(struct mlx5e_hairpin *hp)
{
	mlx5_core_destroy_tir(hp->func_mdev, hp->tirn);
	mlx5_core_dealloc_transport_domain(hp->func_mdev, hp->tdn);
}