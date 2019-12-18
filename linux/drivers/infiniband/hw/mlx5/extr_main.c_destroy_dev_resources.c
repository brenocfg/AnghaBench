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
struct mlx5_ib_resources {TYPE_1__* ports; int /*<<< orphan*/  p0; int /*<<< orphan*/  c0; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; int /*<<< orphan*/  s0; int /*<<< orphan*/  s1; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkey_change_work; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_xrcd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_destroy_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_destroy_srq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_dev_resources(struct mlx5_ib_resources *devr)
{
	int port;

	mlx5_ib_destroy_srq(devr->s1, NULL);
	kfree(devr->s1);
	mlx5_ib_destroy_srq(devr->s0, NULL);
	kfree(devr->s0);
	mlx5_ib_dealloc_xrcd(devr->x0, NULL);
	mlx5_ib_dealloc_xrcd(devr->x1, NULL);
	mlx5_ib_destroy_cq(devr->c0, NULL);
	kfree(devr->c0);
	mlx5_ib_dealloc_pd(devr->p0, NULL);
	kfree(devr->p0);

	/* Make sure no change P_Key work items are still executing */
	for (port = 0; port < ARRAY_SIZE(devr->ports); ++port)
		cancel_work_sync(&devr->ports[port].pkey_change_work);
}