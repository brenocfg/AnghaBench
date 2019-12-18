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
struct mlx5dr_domain {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mdev; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dr_domain_caps_uninit (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  dr_domain_uninit_cache (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  dr_domain_uninit_resources (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  mlx5dr_cmd_sync_steering (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

int mlx5dr_domain_destroy(struct mlx5dr_domain *dmn)
{
	if (refcount_read(&dmn->refcount) > 1)
		return -EBUSY;

	/* make sure resources are not used by the hardware */
	mlx5dr_cmd_sync_steering(dmn->mdev);
	dr_domain_uninit_cache(dmn);
	dr_domain_uninit_resources(dmn);
	dr_domain_caps_uninit(dmn);
	mutex_destroy(&dmn->mutex);
	kfree(dmn);
	return 0;
}